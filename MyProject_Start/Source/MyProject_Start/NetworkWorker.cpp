#include "NetworkWorker.h"
#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "MyProject_Start/Player/TutorialCharacter.h"

FNetworkWorker::FNetworkWorker(FString IP, int32 Port)
{
    // 초기화 리스트를 사용하지 않고 명시적으로 대입
    ServerIP = IP;
    ServerPort = Port;
    bRunning = true;
    Socket = nullptr;

    // 소켓 생성
    Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("Default"), false);
}

bool FNetworkWorker::Init()
{
    FIPv4Address Addr;
    FIPv4Address::Parse(ServerIP, Addr);
    TSharedRef<FInternetAddr> TAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
    TAddr->SetIp(Addr.Value);
    TAddr->SetPort(ServerPort);

    if (Socket->Connect(*TAddr))
    {
        UE_LOG(LogTemp, Warning, TEXT("서버에 연결되었습니다!"));
        return true;
    }
    return false;
}

uint32 FNetworkWorker::Run()
{
    while (bRunning)
    {
        // [안전장치] 소켓이 유효하지 않거나 중지 명령이 내려오면 즉시 종료
        if (!Socket || !bRunning) break;

        uint8 Buffer[1024];
        int32 BytesRead = 0;

        // 데이터 수신 (Blocking 방식)
        if (Socket->Recv(Buffer, sizeof(Buffer), BytesRead))
        {
            // 수신 중 중지되었거나 데이터가 없는 경우 방지
            if (!bRunning || BytesRead <= 0) continue;

            uint8 PacketType = Buffer[0];

            // 1. 접속 패킷 처리
            if (PacketType == PKT_JOIN)
            {
                FPacketJoin* JoinPkt = (FPacketJoin*)Buffer;

                // [중요] 스레드 내부 변수에 내 ID를 복사해둡니다. (캐릭터 객체 참조 대신 사용)
                this->CachedMyPlayerId = JoinPkt->MyId;

                AsyncTask(ENamedThreads::GameThread, [this, AssignedId = JoinPkt->MyId]()
                    {
                        // 게임 스레드에서만 안전하게 캐릭터 객체 접근
                        if (IsValid(OwnerCharacter))
                        {
                            OwnerCharacter->MyPlayerId = AssignedId;
                            UE_LOG(LogTemp, Warning, TEXT("나의 플레이어 ID 할당됨: %d"), AssignedId);
                        }
                    });
            }
            // 2. 이동 패킷 처리
            else if (PacketType == PKT_MOVE)
            {
                FPacketMove* MovePkt = (FPacketMove*)Buffer;
                int32 RemoteId = MovePkt->Data.PlayerId;

                // [해결] 63번째 줄: OwnerCharacter 대신 캐시된 ID로 비교하여 크래시 방지
                if (RemoteId == this->CachedMyPlayerId) continue;

                // 패킷 데이터를 로컬 변수로 안전하게 복사
                FVector NewLoc(MovePkt->Data.X, MovePkt->Data.Y, MovePkt->Data.Z);
                float Fwd = MovePkt->Data.ForwardValue;
                float Rght = MovePkt->Data.RightValue;
                bool bSpr = MovePkt->Data.bIsSprinting;

                // 게임 스레드로 작업 전달
                AsyncTask(ENamedThreads::GameThread, [this, RemoteId, NewLoc, Fwd, Rght, bSpr]()
                    {
                        // 게임 스레드 안에서만 안전하게 IsValid 체크 후 실행
                        if (IsValid(OwnerCharacter) && !OwnerCharacter->IsPendingKillPending())
                        {
                            OwnerCharacter->UpdateRemotePlayer(RemoteId, NewLoc, Fwd, Rght, bSpr);
                        }
                    });
            }
        }

        // CPU 과부하 방지를 위한 미세한 대기
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
    Stop(); // 루프 정지

    if (Socket)
    {
        Socket->Close();
        ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(Socket);
        Socket = nullptr;
    }
}

