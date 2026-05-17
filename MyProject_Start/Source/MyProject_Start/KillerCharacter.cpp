#include "KillerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimSequence.h"
#include "DrawDebugHelpers.h"
#include "UObject/ConstructorHelpers.h"
#include "MyProject_Start/BandagePickup.h"
#include "MyProject_Start/MyGameInstance.h"
#include "MyProject_Start/Player/TutorialCharacter.h"
#include "MyProject_Start/NetworkWorker.h"
#include "MyProject_Start/Generator.h"
#include "Kismet/GameplayStatics.h"
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
    FPSMesh->SetHiddenInGame(false);
    FPSMesh->SetRelativeLocation(FirstPersonArmOffset);
    FPSMesh->SetRelativeRotation(FirstPersonArmRotation);

    static ConstructorHelpers::FObjectFinder<USkeletalMesh> FirstPersonArmMesh(
        TEXT("/Script/Engine.SkeletalMesh'/Game/Animation/zombi/zombi_Arm.zombi_Arm'")
    );
    if (FirstPersonArmMesh.Succeeded())
    {
        FPSMesh->SetSkeletalMesh(FirstPersonArmMesh.Object);
        FPSMesh->SetAnimationMode(EAnimationMode::AnimationSingleNode);
    }
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

    static ConstructorHelpers::FObjectFinder<UAnimSequence> FirstPersonAttackAnimationAsset(
        TEXT("/Script/Engine.AnimSequence'/Game/Animation/zombi/arm_Attack.arm_Attack'")
    );
    if (FirstPersonAttackAnimationAsset.Succeeded())
    {
        FirstPersonAttackAnimation = FirstPersonAttackAnimationAsset.Object;
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

    // 3?좎룞?숈묶 ?좎뙐?몄삕???좎뙓?좎슱?쇿뜝?숈삕 ?좎룞?쇿뜝?숈삕?좎룞???좎떗怨ㅼ삕 ?좎룞?쇿뜝?숈삕
    GetMesh()->SetOwnerNoSee(true);

    // ?좎룞?쇿뜝?숈삕 ?좎룞?쇿뜝?숈삕 ?좎룞?쇿뜝?숈삕 ?좎떗源띿삕??
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
        ApplyLocalPlayerInputMode();
        RemoteKillers.Empty();
        RemoteSurvivors.Empty();

        if (NetworkWorker == nullptr)
        {
            FString ServerIP;
            if (UMyGameInstance* GI = GetGameInstance<UMyGameInstance>())
            {
                if (GI->HasValidatedServerConnection())
                {
                    ServerIP = GI->GetServerIP();
                }
            }

            if (ServerIP.IsEmpty())
            {
                UE_LOG(LogTemp, Error, TEXT("Skipping killer network connect because no validated server IP was provided."));
                return;
            }

            NetworkWorker = new FNetworkWorker(ServerIP, FNetworkWorker::GetDefaultServerPort());
            NetworkWorker->SetOwnerKiller(this);
            FRunnableThread::Create(NetworkWorker, TEXT("KillerNetworkThread"));
        }
    }

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Killer Character Spawned"));
    }
}

void AKillerCharacter::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);
    ApplyLocalPlayerInputMode();
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

    PlayerInputComponent->BindAxis("MoveForward", this, &AKillerCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AKillerCharacter::MoveRight);
    PlayerInputComponent->BindAxis("TurnCamera", this, &AKillerCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAxis("LookUp", this, &AKillerCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AKillerCharacter::StartAttack);
    PlayerInputComponent->BindAction("Pickup", IE_Pressed, this, &AKillerCharacter::PickupSurvivor);
}

void AKillerCharacter::ApplyLocalPlayerInputMode()
{
    APlayerController* PC = Cast<APlayerController>(GetController());
    if (!PC || !PC->IsLocalController())
    {
        return;
    }

    FInputModeGameOnly InputMode;
    PC->SetInputMode(InputMode);
    PC->bShowMouseCursor = false;
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
    if (!AttackMontage && !BodyAttackAnimation && !FirstPersonAttackAnimation) return;

    bIsAttacking = true;
    bHasDealtDamage = false;
    GetCharacterMovement()->MaxWalkSpeed = 100.0f;

    if (IsPlayerControlled() && IsLocallyControlled())
    {
        if (FPSMesh && FirstPersonAttackAnimation)
        {
            FPSMesh->SetHiddenInGame(false);
            FPSMesh->PlayAnimation(FirstPersonAttackAnimation, false);
        }
        else if (FPSMesh && AttackMontage)
        {
            if (UAnimInstance* FPSAnimInstance = FPSMesh->GetAnimInstance())
            {
                FPSAnimInstance->Montage_Play(AttackMontage);
            }
        }

        SendActionToServer(ACTION_KILLER_ATTACK);

        FTimerHandle HitCheckTimer;
        GetWorldTimerManager().SetTimer(HitCheckTimer, this, &AKillerCharacter::CheckHit, 0.3f, false);
    }
    else
    {
        if (BodyAttackAnimation)
        {
            PlayTemporaryBodyAnimation(BodyAttackAnimation);
        }
    }

    const float AttackDuration = (IsPlayerControlled() && IsLocallyControlled() && FirstPersonAttackAnimation)
        ? FirstPersonAttackAnimation->GetPlayLength()
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

// ?좎룞???좎뙃?쎌삕?좎룞???좎룞?쇿뜝?⑹슱???좎뙇?덈챿?쇿뜝?깆눦???좎룞?숉떚?좎룞?쇿뜝?숈삕(Notify)?좎룞?쇿뜝?숈삕 ?멨뜝?숈삕?좎룞???좎룞?쇿뜝?숈삕?좎뙃?덈뙋??
void AKillerCharacter::EndAttack()
{
    bIsAttacking = false;
    // ?좎뙐?숈삕 ?좎룞?쇿뜝?숈삕 ?좎뙂?몄삕?좎룞???좎룞?쇿뜝?숈삕
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
    int32 CandidateCount = 0;
    TArray<ATutorialCharacter*> EvaluatedCandidates;

    auto EvaluateCandidate = [&](ATutorialCharacter* Candidate)
    {
        if (!IsValid(Candidate) || Candidate->IsBeingCarried)
        {
            return;
        }

        if (EvaluatedCandidates.Contains(Candidate))
        {
            return;
        }
        EvaluatedCandidates.Add(Candidate);

        ++CandidateCount;

        UCapsuleComponent* CandidateCapsule = Candidate->GetCapsuleComponent();
        const FVector CandidateCenter = CandidateCapsule
            ? CandidateCapsule->GetComponentLocation()
            : Candidate->GetActorLocation();
        const float CandidateRadius = CandidateCapsule
            ? CandidateCapsule->GetScaledCapsuleRadius()
            : 0.0f;

        FVector ToCandidate = CandidateCenter - Start;
        const float ForwardDistance = FVector::DotProduct(ToCandidate, ForwardVector);
        if (ForwardDistance < 0.0f || ForwardDistance > AttackRange)
        {
            UE_LOG(LogTemp, Verbose, TEXT("CheckHit skipped %s: forward distance %.2f / range %.2f"),
                *Candidate->GetName(), ForwardDistance, AttackRange);
            return;
        }

        const float SideDistance = (ToCandidate - ForwardVector * ForwardDistance).Size();
        const float AllowedSideDistance = 100.0f + CandidateRadius;
        if (SideDistance > AllowedSideDistance)
        {
            UE_LOG(LogTemp, Verbose, TEXT("CheckHit skipped %s: side distance %.2f / allowed %.2f"),
                *Candidate->GetName(), SideDistance, AllowedSideDistance);
            return;
        }

        if (ForwardDistance < BestDistance)
        {
            BestDistance = ForwardDistance;
            Victim = Candidate;
        }
    };

    for (TPair<int32, ATutorialCharacter*>& Pair : RemoteSurvivors)
    {
        EvaluateCandidate(Pair.Value);
    }

    TArray<AActor*> FoundSurvivors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATutorialCharacter::StaticClass(), FoundSurvivors);
    for (AActor* Actor : FoundSurvivors)
    {
        EvaluateCandidate(Cast<ATutorialCharacter>(Actor));
    }

    DrawDebugLine(GetWorld(), Start, End, Victim ? FColor::Green : FColor::Red, false, 1.0f, 0, 2.0f);

    if (Victim)
    {
        bHasDealtDamage = true;
        const bool bHasNetworkId = Victim->MyPlayerId != -1;
        if (bHasNetworkId)
        {
            Victim->PlayNetworkHitReaction();
            const int32 HitTargetId = Victim->IsDowned ? -Victim->MyPlayerId : Victim->MyPlayerId;
            SendActionToServer(ACTION_SURVIVOR_HIT, HitTargetId);
        }
        else
        {
            Victim->PlayHitReaction();
        }

        UE_LOG(LogTemp, Warning, TEXT("Hit Target: %s / ID: %d"), *Victim->GetName(), Victim->MyPlayerId);
        DrawDebugSphere(GetWorld(), Victim->GetActorLocation(), 20.0f, 12, FColor::Yellow, false, 1.0f);
    }

    UE_LOG(LogTemp, Warning, TEXT("CheckHit called | candidates = %d | bHasDealtDamage = %s"),
        CandidateCount, bHasDealtDamage ? TEXT("true") : TEXT("false"));
}

// ?좎룞?쇿뜝?숈삕?좎룞???좎룞?쇿뜝?숈삕 ?좎뙃?쎌삕
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

        UE_LOG(LogTemp, Warning, TEXT("Survivor picked up."));

        PlayCarryAnimation();
        if (PickupMontage) PlayAnimMontage(PickupMontage);
        SendActionToServer(ACTION_SURVIVOR_PICKUP, CarriedSurvivor->MyPlayerId);
    }
}

void AKillerCharacter::DropSurvivor()
{
    if (!CarriedSurvivor)
    {
        return;
    }

    CarriedSurvivor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
    CarriedSurvivor->IsBeingCarried = false;
    CarriedSurvivor->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CarriedSurvivor->GetCharacterMovement()->SetDefaultMovementMode();
    CarriedSurvivor = nullptr;
}

void AKillerCharacter::SendLocationToServer()
{
    if (MyPlayerId == -1) return;

    if (NetworkWorker && NetworkWorker->GetSocket())
    {
        FPacketMove MovePkt;
        MovePkt.Type = PKT_MOVE;
        MovePkt.Data.PlayerId = MyPlayerId;
        MovePkt.Data.CharacterType = CHARACTER_KILLER; // ??곸뵥筌?????

        const FVector CurrentLocation = GetActorLocation();
        MovePkt.Data.X = CurrentLocation.X;
        MovePkt.Data.Y = CurrentLocation.Y;
        MovePkt.Data.Z = CurrentLocation.Z;

        const FVector HorizontalVelocity(GetVelocity().X, GetVelocity().Y, 0.0f);
        const bool bHasMeaningfulMovement = HorizontalVelocity.SizeSquared() > 25.0f;
        const float VisualYaw = bHasMeaningfulMovement
            ? HorizontalVelocity.Rotation().Yaw
            : GetActorRotation().Yaw;
        MovePkt.Data.RotationYaw = VisualYaw;

        // [餓λ쵐?? ??얜즲 ?④쑴沅???????낆젾揶쏅???筌욊낯???節뚮뮸??덈뼄.
        MovePkt.Data.ForwardValue = MoveForwardValue;
        MovePkt.Data.RightValue = MoveRightValue;
        MovePkt.Data.bIsSprinting = false;
        MovePkt.Data.CurrentHealth = 2;
        MovePkt.Data.bIsDowned = false;
        MovePkt.Data.bIsBeingCarried = false;

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

void AKillerCharacter::UpdateRemoteSurvivor(int32 PlayerId, FVector Location, float RotationYaw, float Forward, float Right, bool bSprint, int32 InHealth, bool bInDowned, bool bInBeingCarried)
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
            Target->SyncRemoteState(InHealth, bInDowned, bInBeingCarried);
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
        NewSurvivor->SyncRemoteState(InHealth, bInDowned, bInBeingCarried);
        NewSurvivor->DisableInput(nullptr);
        RemoteSurvivors.Add(PlayerId, NewSurvivor);
        UE_LOG(LogTemp, Warning, TEXT("New Remote Survivor Spawned! ID: %d"), PlayerId);
    }
}
void AKillerCharacter::SendActionToServer(uint8 ActionType, int32 TargetId)
{
    if (!NetworkWorker || !NetworkWorker->GetSocket()) return;

    FPacketAction ActionPkt;
    ActionPkt.Type = PKT_ACTION; // Shared.h???類ㅼ벥??????
    ActionPkt.ActionType = ActionType;
    ActionPkt.InstigatorId = MyPlayerId;
    ActionPkt.TargetId = TargetId;

    // ?袁⑹삺 ?袁⑺뒄?? ???읈揶쏅?猷?揶쏆늿????쇰선 癰귣?源??덈뼄 (??삘뀲 ????癒?퐣 ?類μ넇???袁⑺뒄??癰귣똻??袁⑥쨯)
    FVector Loc = GetActorLocation();
    ActionPkt.X = Loc.X;
    ActionPkt.Y = Loc.Y;
    ActionPkt.Z = Loc.Z;
    ActionPkt.RotationYaw = GetActorRotation().Yaw;
    ActionPkt.RotationYaw = GetActorRotation().Yaw;

    int32 BytesSent = 0;
    NetworkWorker->GetSocket()->Send((uint8*)&ActionPkt, sizeof(FPacketAction), BytesSent);
}



AGenerator* AKillerCharacter::FindGeneratorForNetworkAction(int32 GeneratorId, const FVector& Location) const
{
    UWorld* World = GetWorld();
    if (!World) return nullptr;

    TArray<AActor*> FoundGenerators;
    UGameplayStatics::GetAllActorsOfClass(World, AGenerator::StaticClass(), FoundGenerators);

    AGenerator* NearestGenerator = nullptr;
    float BestDistanceSq = TNumericLimits<float>::Max();

    for (AActor* Actor : FoundGenerators)
    {
        AGenerator* Generator = Cast<AGenerator>(Actor);
        if (!Generator) continue;

        if (Generator->GetGeneratorId() == GeneratorId)
        {
            return Generator;
        }

        const float DistanceSq = FVector::DistSquared(Generator->GetActorLocation(), Location);
        if (DistanceSq < BestDistanceSq)
        {
            BestDistanceSq = DistanceSq;
            NearestGenerator = Generator;
        }
    }

    return NearestGenerator;
}

void AKillerCharacter::ApplyGeneratorNetworkAction(uint8 ActionType, int32 GeneratorId, const FVector& Location, float RepairProgress)
{
    AGenerator* Generator = FindGeneratorForNetworkAction(GeneratorId, Location);
    if (!Generator) return;

    if (ActionType == ACTION_GENERATOR_START)
    {
        Generator->ApplyNetworkRepairState(true, false, RepairProgress);
    }
    else if (ActionType == ACTION_GENERATOR_CANCEL)
    {
        Generator->ApplyNetworkRepairState(false, false, RepairProgress);
    }
    else if (ActionType == ACTION_GENERATOR_COMPLETE)
    {
        Generator->ApplyNetworkRepairState(false, true, 1.f);
    }
}
void AKillerCharacter::HandleNetworkAction(uint8 ActionType, int32 InstigatorId, int32 TargetId, FVector Location, float RotationYaw)
{
    if (ActionType == ACTION_GENERATOR_START || ActionType == ACTION_GENERATOR_CANCEL || ActionType == ACTION_GENERATOR_COMPLETE)
    {
        if (RemoteSurvivors.Contains(InstigatorId) && IsValid(RemoteSurvivors[InstigatorId]))
        {
            RemoteSurvivors[InstigatorId]->SetRepairingGenerator(ActionType == ACTION_GENERATOR_START);
            RemoteSurvivors[InstigatorId]->IsInteracting = (ActionType == ACTION_GENERATOR_START);
        }

        ApplyGeneratorNetworkAction(ActionType, TargetId, Location, RotationYaw);
        return;
    }

    if (ActionType == ACTION_SURVIVOR_REVIVE_START || ActionType == ACTION_SURVIVOR_REVIVE_CANCEL || ActionType == ACTION_SURVIVOR_REVIVE_COMPLETE)
    {
        ATutorialCharacter* Reviver = nullptr;
        if (RemoteSurvivors.Contains(InstigatorId) && IsValid(RemoteSurvivors[InstigatorId]))
        {
            Reviver = RemoteSurvivors[InstigatorId];
        }

        ATutorialCharacter* Survivor = nullptr;
        if (RemoteSurvivors.Contains(TargetId) && IsValid(RemoteSurvivors[TargetId]))
        {
            Survivor = RemoteSurvivors[TargetId];
        }

        if (ActionType == ACTION_SURVIVOR_REVIVE_START)
        {
            if (Reviver)
            {
                Reviver->IsInteracting = true;
                Reviver->SetRevivingSurvivor(true);
            }

            if (Survivor)
            {
                Survivor->bIsBeingRevived = true;
            }
        }
        else if (ActionType == ACTION_SURVIVOR_REVIVE_CANCEL)
        {
            if (Reviver)
            {
                Reviver->StopInteractingWithCurrentTarget(true);
            }

            if (Survivor)
            {
                Survivor->bIsBeingRevived = false;
                Survivor->RecoveryProgress = 0.0f;
            }
        }
        else if (ActionType == ACTION_SURVIVOR_REVIVE_COMPLETE)
        {
            if (Survivor && Survivor->IsDowned)
            {
                Survivor->CompleteInteract_Implementation();
            }

            if (Reviver)
            {
                Reviver->StopInteractingWithCurrentTarget(true);
            }
        }

        return;
    }

    if (ActionType == ACTION_SELF_REVIVE_START || ActionType == ACTION_SELF_REVIVE_CANCEL || ActionType == ACTION_SELF_REVIVE_COMPLETE)
    {
        ATutorialCharacter* Survivor = nullptr;
        if (RemoteSurvivors.Contains(TargetId) && IsValid(RemoteSurvivors[TargetId]))
        {
            Survivor = RemoteSurvivors[TargetId];
        }

        if (!Survivor)
        {
            return;
        }

        if (ActionType == ACTION_SELF_REVIVE_START)
        {
            Survivor->bIsBeingRevived = true;
            Survivor->bIsSelfReviving = true;
            Survivor->IsInteracting = true;
        }
        else if (ActionType == ACTION_SELF_REVIVE_CANCEL)
        {
            Survivor->bIsBeingRevived = false;
            Survivor->bIsSelfReviving = false;
            Survivor->RecoveryProgress = 0.0f;
            Survivor->IsInteracting = false;
        }
        else if (ActionType == ACTION_SELF_REVIVE_COMPLETE)
        {
            Survivor->SetHasBandage(false);
            if (Survivor->IsDowned)
            {
                Survivor->CompleteInteract_Implementation();
            }
        }

        return;
    }

    if (ActionType == ACTION_BANDAGE_PICKUP)
    {
        TArray<AActor*> FoundBandages;
        UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABandagePickup::StaticClass(), FoundBandages);

        for (AActor* Actor : FoundBandages)
        {
            ABandagePickup* BandagePickup = Cast<ABandagePickup>(Actor);
            if (!BandagePickup) continue;

            if (BandagePickup->GetBandageId() == TargetId || FVector::DistSquared(BandagePickup->GetActorLocation(), Location) < 2500.0f)
            {
                BandagePickup->ApplyCollectedState();
                break;
            }
        }

        if (RemoteSurvivors.Contains(InstigatorId) && IsValid(RemoteSurvivors[InstigatorId]))
        {
            RemoteSurvivors[InstigatorId]->SetHasBandage(true);
        }

        return;
    }

    if (ActionType == ACTION_KILLER_ATTACK)
    {
        if (RemoteKillers.Contains(InstigatorId) && IsValid(RemoteKillers[InstigatorId]))
        {
            AKillerCharacter* RemoteKiller = RemoteKillers[InstigatorId];
            RemoteKiller->SetActorLocation(Location);
            RemoteKiller->SetActorRotation(FRotator(0.0f, RotationYaw, 0.0f));

            // StartAttack() ?????袁⑸뻿 ?醫딅빍筌롫뗄???롮춸 獄쏅뗀以?揶쏅벡????源??쀪땀 (?얜똾釉??룐뫂遊?獄쎻뫗?)
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




