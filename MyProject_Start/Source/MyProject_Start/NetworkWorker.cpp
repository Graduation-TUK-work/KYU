#include "NetworkWorker.h"
#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Misc/ConfigCacheIni.h"
#include "MyProject_Start/Player/TutorialCharacter.h"
#include "SpawnPoint.h"
#include "MyProject_Start/KillerCharacter.h"
#include "Kismet/GameplayStatics.h"
namespace
{
    constexpr TCHAR NetworkConfigSection[] = TEXT("/Script/MyProject_Start.NetworkSettings");
    constexpr TCHAR ServerIpKey[] = TEXT("ServerIP");
    constexpr TCHAR ServerPortKey[] = TEXT("ServerPort");
    constexpr TCHAR DefaultServerIp[] = TEXT("127.0.0.1");
    constexpr int32 DefaultServerPort = 7777;
}

FNetworkWorker::FNetworkWorker(FString IP, int32 Port)
{
    ServerIP = IP;
    ServerPort = Port;
    bRunning = true;
    Socket = nullptr;
    OwnerTutorialCharacter = nullptr;
    OwnerKillerCharacter = nullptr;

    Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("Default"), false);
}

FString FNetworkWorker::GetDefaultServerIP()
{
    FString ConfiguredIP = DefaultServerIp; // 기본값 127.0.0.1

    // [핵심 추가] 실행할 때 넘겨준 -IP= 주소가 있는지 먼저 확인합니다.
    if (FParse::Value(FCommandLine::Get(), TEXT("-IP="), ConfiguredIP))
    {
        UE_LOG(LogTemp, Warning, TEXT("Command Line IP Found: %s"), *ConfiguredIP);
        return ConfiguredIP;
    }

    // 기존 INI 로직 (만약을 위해 남겨둠)
    if (GConfig)
    {
        GConfig->GetString(NetworkConfigSection, ServerIpKey, ConfiguredIP, GGameIni);
    }

    ConfiguredIP.TrimStartAndEndInline();
    return ConfiguredIP.IsEmpty() ? FString(DefaultServerIp) : ConfiguredIP;
}

int32 FNetworkWorker::GetDefaultServerPort()
{
    int32 ConfiguredPort = DefaultServerPort;
    if (GConfig)
    {
        GConfig->GetInt(NetworkConfigSection, ServerPortKey, ConfiguredPort, GGameIni);
    }

    return ConfiguredPort > 0 ? ConfiguredPort : DefaultServerPort;
}

bool FNetworkWorker::Init()
{
    FIPv4Address Addr;
    if (!FIPv4Address::Parse(ServerIP, Addr))
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid server IP: %s"), *ServerIP);
        return false;
    }

    TSharedRef<FInternetAddr> TAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
    TAddr->SetIp(Addr.Value);
    TAddr->SetPort(ServerPort);

    UE_LOG(LogTemp, Warning, TEXT("Trying server connection: %s:%d"), *ServerIP, ServerPort);

    if (Socket->Connect(*TAddr))
    {
        UE_LOG(LogTemp, Warning, TEXT("Connected to server: %s:%d"), *ServerIP, ServerPort);
        return true;
    }

    UE_LOG(LogTemp, Error, TEXT("Failed to connect to server: %s:%d"), *ServerIP, ServerPort);
    return false;
}

uint32 FNetworkWorker::Run()
{
    while (bRunning)
    {
        if (!Socket || !bRunning) break;

        uint8 Buffer[4096];
        int32 BytesRead = 0;

        if (Socket->Recv(Buffer, sizeof(Buffer), BytesRead))
        {
            if (!bRunning || BytesRead <= 0) continue;

            int32 Offset = 0;
            while (Offset < BytesRead)
            {
                const uint8 PacketType = Buffer[Offset];
                int32 PacketSize = 0;

                if (PacketType == PKT_JOIN)
                {
                    PacketSize = sizeof(FPacketJoin);
                }
                else if (PacketType == PKT_MOVE)
                {
                    PacketSize = sizeof(FPacketMove);
                }
                else if (PacketType == PKT_ACTION)
                {
                    PacketSize = sizeof(FPacketAction);
                }
                else
                {
                    UE_LOG(LogTemp, Warning, TEXT("Unknown packet type: %d"), PacketType);
                    break;
                }

                if (Offset + PacketSize > BytesRead)
                {
                    break;
                }

                uint8* PacketData = Buffer + Offset;

                if (PacketType == PKT_JOIN)
                {
                    FPacketJoin* JoinPkt = (FPacketJoin*)PacketData;
                    this->CachedMyPlayerId = JoinPkt->MyId;

                    AsyncTask(ENamedThreads::GameThread, [this, AssignedId = JoinPkt->MyId]()
                        {
                            // 1. 내가 서버의 첫 접속자(ID: 0)라서 살인마로 지정되었다면!
                            if (AssignedId == 0)
                            {
                                if (IsValid(OwnerTutorialCharacter))
                                {
                                    UWorld* World = OwnerTutorialCharacter->GetWorld();
                                    APlayerController* PC = Cast<APlayerController>(OwnerTutorialCharacter->GetController());

                                    if (World && PC)
                                    {
                                        // ---- [수정된 부분: SpawnPoint 찾기] ----
                                        FTransform SpawnTransform = OwnerTutorialCharacter->GetActorTransform(); // 기본값: 현재 위치

                                        TArray<AActor*> FoundPoints;
                                        UGameplayStatics::GetAllActorsOfClass(World, ASpawnPoint::StaticClass(), FoundPoints);

                                        for (AActor* Point : FoundPoints)
                                        {
                                            ASpawnPoint* SP = Cast<ASpawnPoint>(Point);
                                            if (SP && SP->SpawnTeam == ETeamType::Killer) // 킬러용 스폰 포인트를 찾으면
                                            {
                                                SpawnTransform = SP->GetActorTransform();
                                                break; // 찾았으니 루프 종료
                                            }
                                        }
                                        // ----------------------------------------

                                        // 살인마 스폰 (찾아낸 SpawnTransform 위치에서 스폰)
                                        AKillerCharacter* NewKiller = World->SpawnActorDeferred<AKillerCharacter>(AKillerCharacter::StaticClass(), SpawnTransform);
                                        if (NewKiller)
                                        {
                                            // 생존자가 쓰던 통신망(NetworkWorker)을 살인마에게 그대로 물려줌
                                            NewKiller->NetworkWorker = this;
                                            NewKiller->MyPlayerId = AssignedId;

                                            // 스폰 완료 및 빙의 (Possess)
                                            NewKiller->FinishSpawning(SpawnTransform);
                                            PC->Possess(NewKiller);

                                            // --- 기존에 작성하신 기존 생존자 안전 삭제 로직 유지 ---
                                            ATutorialCharacter* OldSurvivor = OwnerTutorialCharacter;
                                            this->SetOwnerKiller(NewKiller);
                                            if (OldSurvivor)
                                            {
                                                OldSurvivor->NetworkWorker = nullptr;
                                                OldSurvivor->Destroy();
                                            }

                                            UE_LOG(LogTemp, Warning, TEXT("Swapped to Killer at SpawnPoint! Assigned ID: %d"), AssignedId);
                                        }
                                    }
                                }
                            }
                            // 2. 내가 생존자(ID 1 이상)로 지정되었다면
                            else
                            {
                                if (IsValid(OwnerTutorialCharacter))
                                {
                                    OwnerTutorialCharacter->MyPlayerId = AssignedId;
                                    UE_LOG(LogTemp, Warning, TEXT("Assigned survivor ID: %d"), AssignedId);

                                    // ---- [생존자도 스폰 위치로 이동시키고 싶다면 추가] ----
                                    UWorld* World = OwnerTutorialCharacter->GetWorld();
                                    if (World)
                                    {
                                        TArray<AActor*> FoundPoints;
                                        UGameplayStatics::GetAllActorsOfClass(World, ASpawnPoint::StaticClass(), FoundPoints);
                                        for (AActor* Point : FoundPoints)
                                        {
                                            ASpawnPoint* SP = Cast<ASpawnPoint>(Point);
                                            if (SP && SP->SpawnTeam == ETeamType::Survivor) // 생존자용 스폰 포인트를 찾으면
                                            {
                                                // 새로 스폰할 필요 없이 기존 몸통을 해당 위치로 순간이동
                                                OwnerTutorialCharacter->SetActorTransform(SP->GetActorTransform(), false, nullptr, ETeleportType::TeleportPhysics);
                                                break;
                                            }
                                        }
                                    }
                                    // -------------------------------------------------------
                                }
                                else if (IsValid(OwnerKillerCharacter))
                                {
                                    OwnerKillerCharacter->MyPlayerId = AssignedId;
                                }
                            }
                        });
                }
                else if (PacketType == PKT_MOVE)
                {
                    FPacketMove* MovePkt = (FPacketMove*)PacketData;
                    int32 RemoteId = MovePkt->Data.PlayerId;

                    if (RemoteId != this->CachedMyPlayerId)
                    {
                        uint8 CharacterType = MovePkt->Data.CharacterType;
                        FVector NewLoc(MovePkt->Data.X, MovePkt->Data.Y, MovePkt->Data.Z);
                        float Yaw = MovePkt->Data.RotationYaw;
                        float Fwd = MovePkt->Data.ForwardValue;
                        float Rght = MovePkt->Data.RightValue;
                        bool bSpr = MovePkt->Data.bIsSprinting;

                        AsyncTask(ENamedThreads::GameThread, [this, RemoteId, CharacterType, NewLoc, Yaw, Fwd, Rght, bSpr]()
                            {
                                if (IsValid(OwnerTutorialCharacter) && !OwnerTutorialCharacter->IsPendingKillPending())
                                {
                                    if (CharacterType == CHARACTER_KILLER)
                                    {
                                        OwnerTutorialCharacter->UpdateRemoteKiller(RemoteId, NewLoc, Yaw, Fwd, Rght, bSpr);
                                    }
                                    else
                                    {
                                        OwnerTutorialCharacter->UpdateRemotePlayer(RemoteId, NewLoc, Yaw, Fwd, Rght, bSpr);
                                    }
                                }
                                else if (IsValid(OwnerKillerCharacter) && !OwnerKillerCharacter->IsPendingKillPending())
                                {
                                    if (CharacterType == CHARACTER_KILLER)
                                    {
                                        OwnerKillerCharacter->UpdateRemoteKiller(RemoteId, NewLoc, Yaw, Fwd, Rght, bSpr);
                                    }
                                    else
                                    {
                                        OwnerKillerCharacter->UpdateRemoteSurvivor(RemoteId, NewLoc, Yaw, Fwd, Rght, bSpr);
                                    }
                                }
                            });
                    }
                }
                else if (PacketType == PKT_ACTION)
                {
                    FPacketAction* ActionPkt = (FPacketAction*)PacketData;

                    if (ActionPkt->InstigatorId != this->CachedMyPlayerId)
                    {
                        uint8 ActionType = ActionPkt->ActionType;
                        int32 InstigatorId = ActionPkt->InstigatorId;
                        int32 TargetId = ActionPkt->TargetId;
                        FVector ActionLocation(ActionPkt->X, ActionPkt->Y, ActionPkt->Z);
                        float ActionYaw = ActionPkt->RotationYaw;

                        AsyncTask(ENamedThreads::GameThread, [this, ActionType, InstigatorId, TargetId, ActionLocation, ActionYaw]()
                            {
                                if (IsValid(OwnerTutorialCharacter) && !OwnerTutorialCharacter->IsPendingKillPending())
                                {
                                    OwnerTutorialCharacter->HandleNetworkAction(ActionType, InstigatorId, TargetId, ActionLocation, ActionYaw);
                                }
                                else if (IsValid(OwnerKillerCharacter) && !OwnerKillerCharacter->IsPendingKillPending())
                                {
                                    OwnerKillerCharacter->HandleNetworkAction(ActionType, InstigatorId, TargetId, ActionLocation, ActionYaw);
                                }
                            });
                    }
                }

                Offset += PacketSize;
            }
        }

        FPlatformProcess::Sleep(0.01f);
    }
    return 0;
}

void FNetworkWorker::Stop()
{
    bRunning = false;
}

FNetworkWorker::~FNetworkWorker()
{
    Stop();

    if (Socket)
    {
        Socket->Close();
        ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(Socket);
        Socket = nullptr;
    }
}