// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject_Start/Player/TutorialCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimSequence.h"
#include "Animation/AnimInstance.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "MyProject_Start/InteractionInterface.h"
#include "MyProject_Start/NetworkWorker.h" // �߰�
#include "MyProject_Start/KillerCharacter.h"
#include "MyProject_Start/Generator.h"
#include "Networking.h"    // �߰�
#include "Sockets.h"       // �߰�

ATutorialCharacter::ATutorialCharacter()
{
    bCanVault = false;
    PrimaryActorTick.bCanEverTick = true;

    // ī�޶� �� �������� ����
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

    SpringArm->SetupAttachment(GetCapsuleComponent());
    Camera->SetupAttachment(SpringArm);

    SpringArm->TargetArmLength = 300.f;
    SpringArm->SetRelativeLocationAndRotation(
        FVector(0.f, 0.f, 80.f),
        FRotator(0.f, 0.f, 0.f)
    );
    SpringArm->bUsePawnControlRotation = true;

    // �޽� ��ġ �� ȸ�� ����
    GetMesh()->SetRelativeLocationAndRotation(
        FVector(0.f, 0.f, -88.f),
        FRotator(0.f, -90.f, 0.f)
    );

    static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(
        TEXT("/Script/Engine.SkeletalMesh'/Game/Player/Player.Player'")
    );
    if (SM.Succeeded())
    {
        GetMesh()->SetSkeletalMesh(SM.Object);
    }


    static ConstructorHelpers::FObjectFinder<UAnimMontage> HitMontageAsset(
        TEXT("/Script/Engine.AnimMontage'/Game/Animation/player/AM_Big_Kidney_Hit.AM_Big_Kidney_Hit'")
    );
    if (HitMontageAsset.Succeeded())
    {
        HitMontage = HitMontageAsset.Object;
    }

    static ConstructorHelpers::FObjectFinder<UAnimMontage> DownedMontageAsset(
        TEXT("/Script/Engine.AnimMontage'/Game/Animation/player/AM_Fallen_Idle.AM_Fallen_Idle'")
    );
    if (DownedMontageAsset.Succeeded())
    {
        DownedMontage = DownedMontageAsset.Object;
    }

    static ConstructorHelpers::FObjectFinder<UAnimSequence> HitReactionAnimationAsset(
        TEXT("/Script/Engine.AnimSequence'/Game/Animation/player/Big_Kidney_Hit.Big_Kidney_Hit'")
    );
    if (HitReactionAnimationAsset.Succeeded())
    {
        HitReactionAnimation = HitReactionAnimationAsset.Object;
    }

    static ConstructorHelpers::FObjectFinder<UAnimSequence> DownedAnimationAsset(
        TEXT("/Script/Engine.AnimSequence'/Game/Animation/player/Fallen_Idle.Fallen_Idle'")
    );
    if (DownedAnimationAsset.Succeeded())
    {
        DownedAnimation = DownedAnimationAsset.Object;
    }

    
    // �̵� ����
    bUseControllerRotationYaw = false;

    GetCharacterMovement()->bOrientRotationToMovement = true;

    GetCharacterMovement()->RotationRate = FRotator(0.f, 720.0f, 0.f);

    GetCharacterMovement()->MaxAcceleration = 2048.0f;

    GetCharacterMovement()->BrakingDecelerationWalking = 2048.0f;
    GetCharacterMovement()->GroundFriction = 8.0f;
    GetCharacterMovement()->AirControl = 0.2f;

    // ------------------------------------



    NetworkWorker = nullptr;
}

void ATutorialCharacter::BeginPlay()
{
        Super::BeginPlay();

    if (UClass* SurvivorAnimClass = LoadClass<UAnimInstance>(nullptr, TEXT("/Game/BP/ABP_TutorialAnim.ABP_TutorialAnim_C")))
    {
        GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
        GetMesh()->SetAnimInstanceClass(SurvivorAnimClass);
    }

    if (IsPlayerControlled() && IsLocallyControlled())
    {
        RemotePlayers.Empty();
    }

    if (IsPlayerControlled() && IsLocallyControlled())
    {
        NetworkWorker = new FNetworkWorker(FNetworkWorker::GetDefaultServerIP(), FNetworkWorker::GetDefaultServerPort());
        NetworkWorker->SetOwnerCharacter(this);
        FRunnableThread::Create(NetworkWorker, TEXT("NetworkThread"));
    }
}

void ATutorialCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    // ���� ���� �� �����带 �����ϰ� ����
    if (NetworkWorker)
    {
        NetworkWorker->Stop();
        // �޸� ������ �Ҹ��ڿ��� ó����
    }

    Super::EndPlay(EndPlayReason);
    RemotePlayers.Empty();
    RemoteKillers.Empty();
}

void ATutorialCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    TraceForInteractable();

    // �� ĳ������ ��쿡�� ������ ��ġ ����
    if (IsPlayerControlled() && IsLocallyControlled())
    {
        SendLocationToServer();
    }

    if (IsInteracting)
    {
        UE_LOG(LogTemp, Log, TEXT("Current State: INTERACTING..."));
    }

    if (IsInteracting && CurrentInteractable)
    {
        // [추가된 로직] 대상이 발전기인데 이미 수리가 끝났다면?
        if (AGenerator* Generator = Cast<AGenerator>(CurrentInteractable))
        {
            if (Generator->bIsRepaired)
            {
                // 강제로 상호작용 중단
                CancelInteraction();
                return;
            }
        }

        // 수리가 안 끝났을 때만 업데이트 실행
        IInteractionInterface::Execute_UpdateInteract(CurrentInteractable, DeltaTime);
    }

    if (bIsVaultMoving)
    {
        VaultAlpha += DeltaTime * 2.0f;
        if (VaultAlpha >= 1.0f)
        {
            bIsVaultMoving = false;
            bIsVaulting = false;
        }
    }

    if (Controller)
    {
        FRotator ControlRot = Controller->GetControlRotation();
        FRotator ActorRot = GetActorRotation();
        FRotator Delta = UKismetMathLibrary::NormalizedDeltaRotator(ControlRot, ActorRot);
        AimYaw = Delta.Yaw;
        AimPitch = Delta.Pitch;
    }
} 

void ATutorialCharacter::SendLocationToServer()
{
    if (MyPlayerId == -1) return;

    if (NetworkWorker && NetworkWorker->GetSocket())
    {
        FPacketMove MovePkt;
        MovePkt.Type = PKT_MOVE;
        MovePkt.Data.PlayerId = MyPlayerId;
        MovePkt.Data.CharacterType = CHARACTER_SURVIVOR;

        // 1. 위치 및 회전 세팅
        FVector CurLocation = GetActorLocation();
        MovePkt.Data.X = CurLocation.X;
        MovePkt.Data.Y = CurLocation.Y;
        MovePkt.Data.Z = CurLocation.Z;
        MovePkt.Data.RotationYaw = GetActorRotation().Yaw;

        // 2. [수정된 부분] 복잡한 속도 계산을 지우고, 입력값을 그대로 넣습니다!
        MovePkt.Data.ForwardValue = MoveForwardValue;
        MovePkt.Data.RightValue = MoveRightValue;

        // 3. 달리기 상태 세팅 (기존 코드 유지)
        MovePkt.Data.bIsSprinting = (GetCharacterMovement()->MaxWalkSpeed > 350.0f);


        // 4. 서버로 전송
        int32 BytesSent = 0;
        NetworkWorker->GetSocket()->Send((uint8*)&MovePkt, sizeof(FPacketMove), BytesSent);
    }
}

void ATutorialCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATutorialCharacter::MoveForward);
    PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ATutorialCharacter::MoveRight);
    PlayerInputComponent->BindAxis(TEXT("TurnCamera"), this, &ATutorialCharacter::Turn);
    PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ATutorialCharacter::LookUp);

    PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ATutorialCharacter::BeginCrouch);
    PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ATutorialCharacter::EndCrouch);
    PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ATutorialCharacter::BeginSprint);
    PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ATutorialCharacter::EndSprint);
    PlayerInputComponent->BindAction("Vault", IE_Pressed, this, &ATutorialCharacter::TryVault);
    PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ATutorialCharacter::StartInteraction);
    PlayerInputComponent->BindAction("Interact", IE_Released, this, &ATutorialCharacter::CancelInteraction);
}

void ATutorialCharacter::MoveForward(float Value)
{
    MoveForwardValue = Value;
    if (Controller && Value != 0.0f)
    {
        FRotator Rotation = Controller->GetControlRotation();
        FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
        FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        AddMovementInput(Direction, Value);
    }
}

void ATutorialCharacter::MoveRight(float Value)
{
    MoveRightValue = Value;
    if (Controller && Value != 0.0f)
    {
        FRotator Rotation = Controller->GetControlRotation();
        FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
        FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        AddMovementInput(Direction, Value);
    }
}

void ATutorialCharacter::BeginSprint()
{
    // ���� 1000���� 150 ������ 850 ����
    GetCharacterMovement()->MaxWalkSpeed = 350.0f;
}

void ATutorialCharacter::EndSprint()
{
    // ���� 600���� 150 ������ 450 ����
    GetCharacterMovement()->MaxWalkSpeed = 350.0f;
}

void ATutorialCharacter::Turn(float Value) { AddControllerYawInput(Value); }
void ATutorialCharacter::LookUp(float Value) { AddControllerPitchInput(Value); }

void ATutorialCharacter::BeginCrouch() { Crouch(); }
void ATutorialCharacter::EndCrouch() { UnCrouch(); }


void ATutorialCharacter::TryVault()
{
    if (bIsVaulting) return;

    FVector Start = GetActorLocation() + FVector(0, 0, 10);
    FVector End = Start + GetActorForwardVector() * 150;

    FHitResult Hit;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);

    bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params);
    DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 2.0f);

    if (bHit)
    {
        FVector TopStart = Hit.ImpactPoint + FVector(0, 0, 100);
        FVector TopEnd = TopStart + FVector(0, 0, 50);
        FHitResult TopHit;

        FVector Forward = GetActorForwardVector();
        FVector TargetLocation = Hit.ImpactPoint + Forward * 100;
        TargetLocation.Z += 50;

        bool bTopBlocked = GetWorld()->LineTraceSingleByChannel(
            TopHit, TopStart, TopEnd, ECC_Visibility, Params
        );

        if (!bTopBlocked)
        {
            bIsVaulting = true;
            MotionWarping->AddOrUpdateWarpTargetFromLocation(FName("VaultTarget"), TargetLocation);
            if (VaultMontage)
            {
                PlayAnimMontage(VaultMontage);
            }
        }
    }
}

void ATutorialCharacter::TraceForInteractable()
{
    if (!Camera) return; // ī�޶� ������ ���� �� ��

    FHitResult Hit;
    // 1. ī�޶��� ���� ���� ��ġ�� ���� ������ �����ɴϴ�.
    FVector StartLocation = Camera->GetComponentLocation();
    FVector ForwardVector = Camera->GetForwardVector();

    // 2. ������(Start)�� ĳ���� �� ������ 1���� ���� �о���ϴ�. (�ڱ� �ڽ� �浹 ����)
    FVector TraceStart = StartLocation + (ForwardVector * 100.f);

    // 3. ����(End)�� ���������� 300 unit(3����) �� ������ �����մϴ�.
    FVector TraceEnd = TraceStart + (ForwardVector * 300.f);

    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this); // ����(ĳ���� ��ü) ����

    // 4. LineTrace ����
    bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_Visibility, Params);

    AActor* NewInteractable = nullptr;
    if (bHit && Hit.GetActor() && Hit.GetActor()->Implements<UInteractionInterface>())
    {
        NewInteractable = Hit.GetActor();
    }

    // ����� �ٲ�ų� �þ߿��� ����� Cancel ó��
    if (CurrentInteractable != NewInteractable)
    {
        if (IsInteracting && CurrentInteractable)
        {
            IInteractionInterface::Execute_CancelInteract(CurrentInteractable);
            IsInteracting = false;
        }
        CurrentInteractable = NewInteractable;
    }
}

void ATutorialCharacter::StartInteraction()
{
    if (CurrentInteractable)
    {
        // [추가된 로직] 이미 수리된 발전기인지 확인
        if (AGenerator* Generator = Cast<AGenerator>(CurrentInteractable))
        {
            if (Generator->bIsRepaired)
            {
                UE_LOG(LogTemp, Warning, TEXT("This generator is already done!"));
                return; // 함수 종료
            }
        }

        IInteractionInterface::Execute_StartInteract(CurrentInteractable, this);
        IsInteracting = true;
    }
}

void ATutorialCharacter::CancelInteraction()
{
    if (IsInteracting && CurrentInteractable)
    {
        IInteractionInterface::Execute_CancelInteract(CurrentInteractable);
        IsInteracting = false;
    }
}

void ATutorialCharacter::PlayHitReaction()
{
    ApplyHitReaction(true);
}

void ATutorialCharacter::PlayNetworkHitReaction()
{
    ApplyHitReaction(false);
}

void ATutorialCharacter::ForceDownedState()
{
    CurrentHealth = 0;
    IsDowned = true;
    bCanBeHit = false;

    if (DownedAnimation)
    {
        PlayLoopBodyAnimation(DownedAnimation);
    }
    else if (DownedMontage)
    {
        PlayAnimMontage(DownedMontage);
    }

    GetCapsuleComponent()->SetCapsuleHalfHeight(30.0f);
    GetCharacterMovement()->DisableMovement();
    bUseControllerRotationYaw = false;

    UE_LOG(LogTemp, Error, TEXT("������ ��� ����(Downed)!"));
}
void ATutorialCharacter::ApplyHitReaction(bool bRespectCooldown)
{
    if (IsDowned) return;
    if (bRespectCooldown && !bCanBeHit) return;

    bCanBeHit = false;
    CurrentHealth--;
    UE_LOG(LogTemp, Warning, TEXT("������ �ǰݵ�! ���� ü��: %d"), CurrentHealth);

    if (CurrentHealth > 0)
    {
        if (HitReactionAnimation)
        {
            PlayTemporaryBodyAnimation(HitReactionAnimation);
        }
        else if (HitMontage)
        {
            PlayAnimMontage(HitMontage);
        }

        FTimerHandle HitCooldownTimer;
        GetWorldTimerManager().SetTimer(HitCooldownTimer, FTimerDelegate::CreateLambda([this]()
            {
                bCanBeHit = true;
                UE_LOG(LogTemp, Log, TEXT("������ ���� �ٽ� ���� �� ����"));
            }), 1.0f, false);
    }
    else
    {
        ForceDownedState();

    }
}

void ATutorialCharacter::UpdateRemotePlayer(int32 PlayerId, FVector Location, float RotationYaw, float Forward, float Right, bool bSprint)
{
    UWorld* World = GetWorld();
    if (!World || World->bIsTearingDown) return;
    if (!IsValid(this)) return;

    // 1. �ʿ� �ش� ID�� �ִ��� Ȯ��
    if (RemotePlayers.Contains(PlayerId))
    {
        // �����ϰ� ĳ���ͷ� ����ȯ
        ATutorialCharacter* Target = Cast<ATutorialCharacter>(RemotePlayers[PlayerId]);

        // [����] Target�� �޸𸮿� ����ֱ⸸ �ϸ� ������Ʈ ����
        if (IsValid(Target))
        {
            Target->SetActorLocation(Location);
            Target->SetActorRotation(FRotator(0.0f, RotationYaw, 0.0f));

            Target->RemoteForwardValue = Forward;
            Target->RemoteRightValue = Right;
            Target->RemoteIsSprinting = bSprint;

            // ���⼭ �Լ� ���� (���������� ������Ʈ��)
            return;
        }
        else
        {
            // ������ �÷��� ������ ������ٸ� �ʿ��� ����
            RemotePlayers.Remove(PlayerId);
        }
    }

    // 2. �ʿ� ���ų� Target�� ��ȿ���� ���� ��쿡�� ���� (���Ⱑ else ���� ���� ��)
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    ATutorialCharacter* NewPlayer = World->SpawnActor<ATutorialCharacter>(GetClass(), Location, FRotator(0.0f, RotationYaw, 0.0f), SpawnParams);

    if (NewPlayer)
    {
        NewPlayer->MyPlayerId = PlayerId;
        // �ʿ� Ȯ���� ���
        NewPlayer->AutoPossessPlayer = EAutoReceiveInput::Disabled;
        NewPlayer->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        NewPlayer->DisableInput(nullptr);
        RemotePlayers.Add(PlayerId, NewPlayer);
        UE_LOG(LogTemp, Warning, TEXT("New Remote Player Spawned! ID: %d"), PlayerId);
    }
}
void ATutorialCharacter::UpdateRemoteKiller(int32 PlayerId, FVector Location, float RotationYaw, float Forward, float Right, bool bSprint)
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

            // =========================================================
            // [핵심 추가] 서버에서 받은 애니메이션 입력값을 킬러에게 주입!
            // =========================================================
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

        // =========================================================
        // [핵심 추가] 처음 스폰될 때도 초기 이동 값을 넣어줍니다.
        // =========================================================
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

void ATutorialCharacter::HandleNetworkAction(uint8 ActionType, int32 InstigatorId, int32 TargetId, FVector Location, float RotationYaw)
{
    if (ActionType == ACTION_KILLER_ATTACK)
    {
        if (RemoteKillers.Contains(InstigatorId) && IsValid(RemoteKillers[InstigatorId]))
        {
            RemoteKillers[InstigatorId]->SetActorLocation(Location);
            RemoteKillers[InstigatorId]->SetActorRotation(FRotator(0.0f, RotationYaw, 0.0f));
            RemoteKillers[InstigatorId]->StartAttack();
        }
        return;
    }

    if (ActionType == ACTION_SURVIVOR_HIT)
    {
        const bool bForceDown = TargetId < 0;
        const int32 RealTargetId = bForceDown ? -TargetId : TargetId;

        if (RealTargetId == MyPlayerId || (RealTargetId > 0 && !RemotePlayers.Contains(RealTargetId)))
        {
            if (bForceDown)
            {
                ForceDownedState();
            }
            else
            {
                PlayNetworkHitReaction();
            }
        }
        else if (RemotePlayers.Contains(RealTargetId) && IsValid(RemotePlayers[RealTargetId]))
        {
            if (bForceDown)
            {
                RemotePlayers[RealTargetId]->ForceDownedState();
            }
            else
            {
                RemotePlayers[RealTargetId]->PlayNetworkHitReaction();
            }
        }
        return;
    }

    if (ActionType == ACTION_SURVIVOR_PICKUP)
    {
        AKillerCharacter* Killer = nullptr;
        if (RemoteKillers.Contains(InstigatorId) && IsValid(RemoteKillers[InstigatorId]))
        {
            Killer = RemoteKillers[InstigatorId];
        }

        ATutorialCharacter* Survivor = nullptr;
        if (TargetId == MyPlayerId)
        {
            Survivor = this;
        }
        else if (RemotePlayers.Contains(TargetId) && IsValid(RemotePlayers[TargetId]))
        {
            Survivor = RemotePlayers[TargetId];
        }

        if (Killer && Survivor)
        {
            Survivor->IsBeingCarried = true;
            Survivor->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
            Survivor->GetCharacterMovement()->DisableMovement();
            Survivor->AttachToComponent(Killer->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("CarrySocket"));
            Killer->PlayCarryAnimation();
        }
    }
}

void ATutorialCharacter::PlayTemporaryBodyAnimation(UAnimSequence* Animation)
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
        &ATutorialCharacter::RestoreBodyAnimClass,
        Animation->GetPlayLength(),
        false
    );
}

void ATutorialCharacter::PlayLoopBodyAnimation(UAnimSequence* Animation)
{
    if (!Animation || !GetMesh())
    {
        return;
    }

    GetMesh()->PlayAnimation(Animation, true);
}

void ATutorialCharacter::RestoreBodyAnimClass()
{
    if (GetMesh() && !IsDowned && !IsBeingCarried)
    {
        if (UClass* SurvivorAnimClass = LoadClass<UAnimInstance>(nullptr, TEXT("/Game/BP/ABP_TutorialAnim.ABP_TutorialAnim_C")))
        {
            GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
            GetMesh()->SetAnimInstanceClass(SurvivorAnimClass);
        }
    }
}