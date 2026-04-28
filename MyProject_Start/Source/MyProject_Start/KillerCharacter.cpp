#include "KillerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimSequence.h"
#include "DrawDebugHelpers.h"
#include "UObject/ConstructorHelpers.h"
#include "MyProject_Start/Player/TutorialCharacter.h"
#include "MyProject_Start/NetworkWorker.h"
#include "Networking.h"
#include "Sockets.h"

// Sets default values
AKillerCharacter::AKillerCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    GetCharacterMovement()->MaxWalkSpeed = 400.0f;

    FPSCamerComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
    FPSCamerComponent->SetupAttachment(GetCapsuleComponent());
    FPSCamerComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
    FPSCamerComponent->bUsePawnControlRotation = true;

    FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
    FPSMesh->SetOnlyOwnerSee(true);
    FPSMesh->SetupAttachment(FPSCamerComponent);
    FPSMesh->bCastDynamicShadow = false;
    FPSMesh->CastShadow = false;

    FPSMesh->BoundsScale = 5.0f;
    GetMesh()->SetRelativeLocationAndRotation(
        FVector(0.0f, 0.0f, -88.0f),
        FRotator(0.0f, -90.0f, 0.0f)
    );

    static ConstructorHelpers::FObjectFinder<USkeletalMesh> KillerMesh(
        TEXT("/Script/Engine.SkeletalMesh'/Game/zombi/zombi.zombi'")
    );
    if (KillerMesh.Succeeded())
    {
        GetMesh()->SetSkeletalMesh(KillerMesh.Object);
    }


    static ConstructorHelpers::FObjectFinder<UAnimMontage> AttackMontageAsset(
        TEXT("/Script/Engine.AnimMontage'/Game/Animation/zombi/AM_arm_Attack.AM_arm_Attack'")
    );
    if (AttackMontageAsset.Succeeded())
    {
        AttackMontage = AttackMontageAsset.Object;
    }

    static ConstructorHelpers::FObjectFinder<UAnimSequence> BodyAttackAnimationAsset(
        TEXT("/Script/Engine.AnimSequence'/Game/Animation/zombi/atack.atack'")
    );
    if (BodyAttackAnimationAsset.Succeeded())
    {
        BodyAttackAnimation = BodyAttackAnimationAsset.Object;
    }

    static ConstructorHelpers::FObjectFinder<UAnimSequence> CarryAnimationAsset(
        TEXT("/Script/Engine.AnimSequence'/Game/Animation/zombi/Walk_With.Walk_With'")
    );
    if (CarryAnimationAsset.Succeeded())
    {
        CarryAnimation = CarryAnimationAsset.Object;
    }

    // 3��Ī �ٵ�� �ڽſ��� ������ �ʰ� ����
    GetMesh()->SetOwnerNoSee(true);

    // ���� ���� ���� �ʱ�ȭ
    bIsAttacking = false;


    NetworkWorker = nullptr;
}

void AKillerCharacter::BeginPlay()
{
        Super::BeginPlay();

    if (UClass* KillerAnimClass = LoadClass<UAnimInstance>(nullptr, TEXT("/Game/BP/ABP_Zombi.ABP_Zombi_C")))
    {
        GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
        GetMesh()->SetAnimInstanceClass(KillerAnimClass);
    }

    if (FPSMesh)
    {
        if (UClass* KillerArmAnimClass = LoadClass<UAnimInstance>(nullptr, TEXT("/Game/BP/ABP_zombi_Arm.ABP_zombi_Arm_C")))
        {
            FPSMesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
            FPSMesh->SetAnimInstanceClass(KillerArmAnimClass);
        }
    }

    if (IsPlayerControlled() && IsLocallyControlled())
    {
        RemoteKillers.Empty();
        RemoteSurvivors.Empty();

        // [수정된 부분] NetworkWorker가 아직 없을 때만 새로 생성합니다.
        // 생존자에서 변신(Swap)해서 넘어온 경우 이미 채워져 있으므로 건너뜁니다.
        if (NetworkWorker == nullptr)
        {
            NetworkWorker = new FNetworkWorker(FNetworkWorker::GetDefaultServerIP(), FNetworkWorker::GetDefaultServerPort());
            NetworkWorker->SetOwnerKiller(this);
            FRunnableThread::Create(NetworkWorker, TEXT("KillerNetworkThread"));
        }
    }

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Killer Character Spawned"));
    }
}

void AKillerCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (NetworkWorker)
    {
        NetworkWorker->Stop();
    }

    Super::EndPlay(EndPlayReason);
    RemoteKillers.Empty();
    RemoteSurvivors.Empty();
}

void AKillerCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    // 1. ���� �̵� �ӵ� ��� (XY ������ �ӵ��� ����)
    FVector Velocity = GetVelocity();
    FVector LateralVelocity = FVector(Velocity.X, Velocity.Y, 0.f);
    MovementSpeed = LateralVelocity.Size();

    if (IsPlayerControlled() && IsLocallyControlled())
    {
        SendLocationToServer();
    }
}

void AKillerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // �̵� �� �ü� ó��
    PlayerInputComponent->BindAxis("MoveForward", this, &AKillerCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AKillerCharacter::MoveRight);
    PlayerInputComponent->BindAxis("TurnCamera", this, &AKillerCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAxis("LookUp", this, &AKillerCharacter::AddControllerPitchInput);

    // ���� �Է� ���ε� (������Ʈ ���� - �Է¿� "Attack"�� ��ϵǾ� �־�� �մϴ�)
    PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AKillerCharacter::StartAttack);
    PlayerInputComponent->BindAction("Pickup", IE_Pressed, this, &AKillerCharacter::PickupSurvivor);
}

void AKillerCharacter::MoveForward(float AxisValue)
{
    MoveForwardValue = AxisValue;
    if (Controller && AxisValue != 0.0f)
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        AddMovementInput(Direction, AxisValue);
    }
}

void AKillerCharacter::MoveRight(float AxisValue)
{
    MoveRightValue = AxisValue;
    if (Controller && AxisValue != 0.0f)
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        AddMovementInput(Direction, AxisValue);
    }
}

void AKillerCharacter::StartAttack()
{
    if (bIsAttacking) return;
    if (!AttackMontage && !BodyAttackAnimation) return;

    bIsAttacking = true;
    bHasDealtDamage = false;

    // 공격 시 살인마 이동 속도 감소 (공격 경직)
    GetCharacterMovement()->MaxWalkSpeed = 100.0f;

    // 1. 내가 직접 조종하는 살인마일 경우
    if (IsPlayerControlled() && IsLocallyControlled())
    {
        // 1인칭 팔 애니메이션 재생
        if (FPSMesh && AttackMontage)
        {
            if (UAnimInstance* FPSAnimInstance = FPSMesh->GetAnimInstance())
            {
                FPSAnimInstance->Montage_Play(AttackMontage);
            }
        }

        // 서버로 "나 공격한다" 패킷 전송
        SendActionToServer(ACTION_KILLER_ATTACK);

        // [중요] 애니메이션이 나가는 중간 쯤(예: 0.3초 뒤)에 데미지 판정 실행
        FTimerHandle HitCheckTimer;
        GetWorldTimerManager().SetTimer(HitCheckTimer, this, &AKillerCharacter::CheckHit, 0.3f, false);
    }
    // 2. 다른 사람 화면에 보이는 원격 살인마일 경우
    else
    {
        // 전신(3인칭) 애니메이션만 재생
        if (BodyAttackAnimation)
        {
            PlayTemporaryBodyAnimation(BodyAttackAnimation);
        }
    }

    // 공격 종료 및 상태 복구 타이머
    const float AttackDuration = (IsPlayerControlled() && IsLocallyControlled() && AttackMontage)
        ? AttackMontage->GetPlayLength()
        : (BodyAttackAnimation ? BodyAttackAnimation->GetPlayLength() : 0.8f);

    FTimerHandle AttackEndTimer;
    GetWorldTimerManager().SetTimer(
        AttackEndTimer,
        this,
        &AKillerCharacter::EndAttack,
        FMath::Max(AttackDuration, 0.2f),
        false
    );
}

// �� �Լ��� ���߿� �ִϸ��̼� ��Ƽ����(Notify)���� ȣ���� �����Դϴ�.
void AKillerCharacter::EndAttack()
{
    bIsAttacking = false;
    // �ٽ� ���� �ӵ��� ����
    GetCharacterMovement()->MaxWalkSpeed = 400.0f;
    UE_LOG(LogTemp, Warning, TEXT("EndAttack called"));
}

void AKillerCharacter::CheckHit()
{
    if (!IsPlayerControlled() || !IsLocallyControlled()) return;
    if (bHasDealtDamage) return;

    FVector Start = FPSCamerComponent->GetComponentLocation();
    FVector ForwardVector = FPSCamerComponent->GetForwardVector().GetSafeNormal();
    FVector End = Start + (ForwardVector * AttackRange);

    ATutorialCharacter* Victim = nullptr;
    float BestDistance = AttackRange;

    for (TPair<int32, ATutorialCharacter*>& Pair : RemoteSurvivors)
    {
        ATutorialCharacter* Candidate = Pair.Value;
        if (!IsValid(Candidate) || Candidate->IsBeingCarried)
        {
            continue;
        }

        FVector ToCandidate = Candidate->GetActorLocation() - Start;
        const float ForwardDistance = FVector::DotProduct(ToCandidate, ForwardVector);
        if (ForwardDistance < 0.0f || ForwardDistance > AttackRange)
        {
            continue;
        }

        const float SideDistance = (ToCandidate - ForwardVector * ForwardDistance).Size();
        if (SideDistance > 100.0f)
        {
            continue;
        }

        if (ForwardDistance < BestDistance)
        {
            BestDistance = ForwardDistance;
            Victim = Candidate;
        }
    }

    DrawDebugLine(GetWorld(), Start, End, Victim ? FColor::Green : FColor::Red, false, 1.0f, 0, 2.0f);

    if (Victim)
    {
        bHasDealtDamage = true;
        Victim->PlayNetworkHitReaction();
        const int32 HitTargetId = Victim->IsDowned ? -Victim->MyPlayerId : Victim->MyPlayerId;
        SendActionToServer(ACTION_SURVIVOR_HIT, HitTargetId);

        UE_LOG(LogTemp, Warning, TEXT("Hit Target: %s / ID: %d"), *Victim->GetName(), Victim->MyPlayerId);
        DrawDebugSphere(GetWorld(), Victim->GetActorLocation(), 20.0f, 12, FColor::Yellow, false, 1.0f);
    }

    UE_LOG(LogTemp, Warning, TEXT("CheckHit called | bHasDealtDamage = %s"), bHasDealtDamage ? TEXT("true") : TEXT("false"));
}

// ������ ���� �Լ�
void AKillerCharacter::PickupSurvivor()
{
    if (CarriedSurvivor) return;

    FVector Start = FPSCamerComponent->GetComponentLocation();
    FVector ForwardVector = FPSCamerComponent->GetForwardVector().GetSafeNormal();

    ATutorialCharacter* Target = nullptr;
    float BestDistance = AttackRange;

    for (TPair<int32, ATutorialCharacter*>& Pair : RemoteSurvivors)
    {
        ATutorialCharacter* Candidate = Pair.Value;
        if (!IsValid(Candidate) || !Candidate->IsDowned || Candidate->IsBeingCarried)
        {
            continue;
        }

        FVector ToCandidate = Candidate->GetActorLocation() - Start;
        const float ForwardDistance = FVector::DotProduct(ToCandidate, ForwardVector);
        if (ForwardDistance < 0.0f || ForwardDistance > AttackRange)
        {
            continue;
        }

        const float SideDistance = (ToCandidate - ForwardVector * ForwardDistance).Size();
        if (SideDistance > 120.0f)
        {
            continue;
        }

        if (ForwardDistance < BestDistance)
        {
            BestDistance = ForwardDistance;
            Target = Candidate;
        }
    }

    if (Target && Target->IsDowned)
    {
        CarriedSurvivor = Target;
        CarriedSurvivor->IsBeingCarried = true;
        CarriedSurvivor->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        CarriedSurvivor->GetCharacterMovement()->DisableMovement();
        CarriedSurvivor->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("CarrySocket"));

        UE_LOG(LogTemp, Warning, TEXT("�����ڸ� ������ϴ�!"));

        PlayCarryAnimation();
        if (PickupMontage) PlayAnimMontage(PickupMontage);
        SendActionToServer(ACTION_SURVIVOR_PICKUP, CarriedSurvivor->MyPlayerId);
    }
}
void AKillerCharacter::SendLocationToServer()
{
    if (MyPlayerId == -1) return;

    if (NetworkWorker && NetworkWorker->GetSocket())
    {
        FPacketMove MovePkt;
        MovePkt.Type = PKT_MOVE;
        MovePkt.Data.PlayerId = MyPlayerId;
        MovePkt.Data.CharacterType = CHARACTER_KILLER; // 살인마 타입

        MovePkt.Data.X = GetActorLocation().X;
        MovePkt.Data.Y = GetActorLocation().Y;
        MovePkt.Data.Z = GetActorLocation().Z;
        MovePkt.Data.RotationYaw = GetActorRotation().Yaw;

        // [중요] 속도 계산 대신 입력값을 직접 넣습니다.
        MovePkt.Data.ForwardValue = MoveForwardValue;
        MovePkt.Data.RightValue = MoveRightValue;
        MovePkt.Data.bIsSprinting = false;

        int32 BytesSent = 0;
        NetworkWorker->GetSocket()->Send((uint8*)&MovePkt, sizeof(FPacketMove), BytesSent);
    }
}

void AKillerCharacter::UpdateRemoteKiller(int32 PlayerId, FVector Location, float RotationYaw, float Forward, float Right, bool bSprint)
{
    UWorld* World = GetWorld();
    if (!World || World->bIsTearingDown) return;
    if (!IsValid(this)) return;

    if (RemoteKillers.Contains(PlayerId))
    {
        AKillerCharacter* Target = Cast<AKillerCharacter>(RemoteKillers[PlayerId]);
        if (IsValid(Target))
        {
            Target->SetActorLocation(Location);
            Target->SetActorRotation(FRotator(0.0f, RotationYaw, 0.0f));
            Target->RemoteForwardValue = Forward;
            Target->RemoteRightValue = Right;
            Target->RemoteMovementSpeed = FVector2D(Forward, Right).Size() * 400.0f;
            return;
        }

        RemoteKillers.Remove(PlayerId);
    }

    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    AKillerCharacter* NewKiller = World->SpawnActor<AKillerCharacter>(AKillerCharacter::StaticClass(), Location, FRotator(0.0f, RotationYaw, 0.0f), SpawnParams);
    if (NewKiller)
    {
        NewKiller->MyPlayerId = PlayerId;
        NewKiller->RemoteForwardValue = Forward;
        NewKiller->RemoteRightValue = Right;
        NewKiller->RemoteMovementSpeed = FVector2D(Forward, Right).Size() * 400.0f;
        NewKiller->AutoPossessPlayer = EAutoReceiveInput::Disabled;
        NewKiller->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        NewKiller->DisableInput(nullptr);
        RemoteKillers.Add(PlayerId, NewKiller);
        UE_LOG(LogTemp, Warning, TEXT("New Remote Killer Spawned! ID: %d"), PlayerId);
    }
}

void AKillerCharacter::UpdateRemoteSurvivor(int32 PlayerId, FVector Location, float RotationYaw, float Forward, float Right, bool bSprint)
{
    UWorld* World = GetWorld();
    if (!World || World->bIsTearingDown) return;
    if (!IsValid(this)) return;

    if (RemoteSurvivors.Contains(PlayerId))
    {
        ATutorialCharacter* Target = Cast<ATutorialCharacter>(RemoteSurvivors[PlayerId]);
        if (IsValid(Target))
        {
            Target->SetActorLocation(Location);
            Target->SetActorRotation(FRotator(0.0f, RotationYaw, 0.0f));
            Target->RemoteForwardValue = Forward;
            Target->RemoteRightValue = Right;
            Target->RemoteIsSprinting = bSprint;
            return;
        }

        RemoteSurvivors.Remove(PlayerId);
    }

    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    ATutorialCharacter* NewSurvivor = World->SpawnActor<ATutorialCharacter>(ATutorialCharacter::StaticClass(), Location, FRotator(0.0f, RotationYaw, 0.0f), SpawnParams);
    if (NewSurvivor)
    {
        NewSurvivor->MyPlayerId = PlayerId;
        NewSurvivor->AutoPossessPlayer = EAutoReceiveInput::Disabled;
        NewSurvivor->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        NewSurvivor->DisableInput(nullptr);
        RemoteSurvivors.Add(PlayerId, NewSurvivor);
        UE_LOG(LogTemp, Warning, TEXT("New Remote Survivor Spawned! ID: %d"), PlayerId);
    }
}
void AKillerCharacter::SendActionToServer(uint8 ActionType, int32 TargetId)
{
    if (!NetworkWorker || !NetworkWorker->GetSocket()) return;

    FPacketAction ActionPkt;
    ActionPkt.Type = PKT_ACTION; // Shared.h에 정의된 타입
    ActionPkt.ActionType = ActionType;
    ActionPkt.InstigatorId = MyPlayerId;
    ActionPkt.TargetId = TargetId;

    // 현재 위치와 회전값도 같이 실어 보냅니다 (다른 클라에서 정확한 위치에 보이도록)
    FVector Loc = GetActorLocation();
    ActionPkt.X = Loc.X;
    ActionPkt.Y = Loc.Y;
    ActionPkt.Z = Loc.Z;
    ActionPkt.RotationYaw = GetActorRotation().Yaw;
    ActionPkt.RotationYaw = GetActorRotation().Yaw;

    int32 BytesSent = 0;
    NetworkWorker->GetSocket()->Send((uint8*)&ActionPkt, sizeof(FPacketAction), BytesSent);
}


void AKillerCharacter::HandleNetworkAction(uint8 ActionType, int32 InstigatorId, int32 TargetId, FVector Location, float RotationYaw)
{
    if (ActionType == ACTION_KILLER_ATTACK)
    {
        if (RemoteKillers.Contains(InstigatorId) && IsValid(RemoteKillers[InstigatorId]))
        {
            AKillerCharacter* RemoteKiller = RemoteKillers[InstigatorId];
            RemoteKiller->SetActorLocation(Location);
            RemoteKiller->SetActorRotation(FRotator(0.0f, RotationYaw, 0.0f));

            // StartAttack() 대신 전신 애니메이션만 바로 강제 재생시킴 (무한 루프 방지)
            if (RemoteKiller->BodyAttackAnimation)
            {
                RemoteKiller->PlayTemporaryBodyAnimation(RemoteKiller->BodyAttackAnimation);
            }
        }
        return;
    }
    if (ActionType == ACTION_SURVIVOR_HIT)
    {
        const bool bForceDown = TargetId < 0;
        const int32 RealTargetId = bForceDown ? -TargetId : TargetId;

        if (RemoteSurvivors.Contains(RealTargetId) && IsValid(RemoteSurvivors[RealTargetId]))
        {
            if (bForceDown)
            {
                RemoteSurvivors[RealTargetId]->ForceDownedState();
            }
            else
            {
                RemoteSurvivors[RealTargetId]->PlayNetworkHitReaction();
            }
        }
        return;
    }

    if (ActionType == ACTION_SURVIVOR_PICKUP)
    {
        AKillerCharacter* Killer = nullptr;
        if (InstigatorId == MyPlayerId)
        {
            Killer = this;
        }
        else if (RemoteKillers.Contains(InstigatorId) && IsValid(RemoteKillers[InstigatorId]))
        {
            Killer = RemoteKillers[InstigatorId];
        }

        ATutorialCharacter* Survivor = nullptr;
        if (RemoteSurvivors.Contains(TargetId) && IsValid(RemoteSurvivors[TargetId]))
        {
            Survivor = RemoteSurvivors[TargetId];
        }

        if (Killer && Survivor)
        {
            Killer->CarriedSurvivor = Survivor;
            Survivor->IsBeingCarried = true;
            Survivor->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
            Survivor->GetCharacterMovement()->DisableMovement();
            Survivor->AttachToComponent(Killer->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("CarrySocket"));
            Killer->PlayCarryAnimation();
        }
    }
}

void AKillerCharacter::PlayTemporaryBodyAnimation(UAnimSequence* Animation)
{
    if (!Animation || !GetMesh())
    {
        return;
    }

    GetMesh()->PlayAnimation(Animation, false);

    FTimerHandle RestoreAnimTimer;
    GetWorldTimerManager().SetTimer(
        RestoreAnimTimer,
        this,
        &AKillerCharacter::RestoreBodyAnimClass,
        Animation->GetPlayLength(),
        false
    );
}

void AKillerCharacter::PlayCarryAnimation()
{
    if (!CarryAnimation || !GetMesh())
    {
        return;
    }

    GetMesh()->PlayAnimation(CarryAnimation, true);
}

void AKillerCharacter::RestoreBodyAnimClass()
{
    bIsAttacking = false;
    bHasDealtDamage = false;

    if (GetMesh())
    {
        if (UClass* KillerAnimClass = LoadClass<UAnimInstance>(nullptr, TEXT("/Game/BP/ABP_Zombi.ABP_Zombi_C")))
        {
            GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
            GetMesh()->SetAnimInstanceClass(KillerAnimClass);
        }
    }
}

