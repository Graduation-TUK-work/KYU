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
#include "Kismet/GameplayStatics.h"
#include "MyProject_Start/InteractionInterface.h"
#include "MyProject_Start/NetworkWorker.h" // 占쌩곤옙
#include "MyProject_Start/KillerCharacter.h"
#include "MyProject_Start/Generator.h"
#include "MyProject_Start/ParkourInteractable.h"
#include "Networking.h"    // 占쌩곤옙
#include "Sockets.h"       // 占쌩곤옙

ATutorialCharacter::ATutorialCharacter()
{
    bCanVault = false;
    PrimaryActorTick.bCanEverTick = true;

    // 카占쌨띰옙 占쏙옙 占쏙옙占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙
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

    // 占쌨쏙옙 占쏙옙치 占쏙옙 회占쏙옙 占쏙옙占쏙옙
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


    static ConstructorHelpers::FObjectFinder<UAnimMontage> NewHitMontageAsset(
        TEXT("/Script/Engine.AnimMontage'/Game/Animation/player/AM_Hit_On_The_Back_Montag.AM_Hit_On_The_Back_Montag'")
    );
    if (NewHitMontageAsset.Succeeded())
    {
        HitMontage = NewHitMontageAsset.Object;
    }

    static ConstructorHelpers::FObjectFinder<UAnimMontage> NewDownedMontageAsset(
        TEXT("/Script/Engine.AnimMontage'/Game/Animation/player/AM_Player_Dying_Anim.AM_Player_Dying_Anim'")
    );
    if (NewDownedMontageAsset.Succeeded())
    {
        DownedMontage = NewDownedMontageAsset.Object;
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

    
    static ConstructorHelpers::FObjectFinder<UAnimSequence> RepairAnimationAsset(
        TEXT("/Script/Engine.AnimSequence'/Game/Animation/player/Cow_Milking.Cow_Milking'")
    );
    if (RepairAnimationAsset.Succeeded())
    {
        RepairAnimation = RepairAnimationAsset.Object;
    }

    static ConstructorHelpers::FObjectFinder<UAnimMontage> RepairMontageAsset(
        TEXT("/Script/Engine.AnimMontage'/Game/Animation/player/AM_Repair.AM_Repair'")
    );
    if (RepairMontageAsset.Succeeded())
    {
        RepairMontage = RepairMontageAsset.Object;
    }
    // 占싱듸옙 占쏙옙占쏙옙
    bUseControllerRotationYaw = false;

    GetCharacterMovement()->bOrientRotationToMovement = true;

    GetCharacterMovement()->RotationRate = FRotator(0.f, 720.0f, 0.f);

    GetCharacterMovement()->MaxAcceleration = 2048.0f;

    GetCharacterMovement()->BrakingDecelerationWalking = 2048.0f;
    GetCharacterMovement()->GroundFriction = 8.0f;
    GetCharacterMovement()->AirControl = 0.2f;

    GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

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
    // 占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙 占쏙옙占쏙옙占썲를 占쏙옙占쏙옙占싹곤옙 占쏙옙占쏙옙
    if (NetworkWorker)
    {
        NetworkWorker->Stop();
        // 占쌨몌옙 占쏙옙占쏙옙占쏙옙 占쌀몌옙占쌘울옙占쏙옙 처占쏙옙占쏙옙
    }

    Super::EndPlay(EndPlayReason);
    RemotePlayers.Empty();
    RemoteKillers.Empty();
}

void ATutorialCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!IsInteracting)
    {
        TraceForInteractable();
    }

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
        AGenerator* Generator = Cast<AGenerator>(CurrentInteractable);
        ATutorialCharacter* DownedSurvivor = Cast<ATutorialCharacter>(CurrentInteractable);
        if (Generator && Generator->bIsRepaired)
        {
            CancelInteraction();
            return;
        }

        if (DownedSurvivor && (!DownedSurvivor->IsDowned || DownedSurvivor->IsBeingCarried))
        {
            StopInteractingWithCurrentTarget(true);
            return;
        }

        const bool bWasGeneratorRepaired = Generator && Generator->bIsRepaired;
        const bool bWasDowned = DownedSurvivor && DownedSurvivor->IsDowned;

        IInteractionInterface::Execute_UpdateInteract(CurrentInteractable, DeltaTime);

        if (Generator && !bWasGeneratorRepaired && Generator->bIsRepaired)
        {
            SendGeneratorActionToServer(ACTION_GENERATOR_COMPLETE, Generator);
            SetRepairingGenerator(false);
            ShowGeneratorRepairCount();
            IsInteracting = false;
        }
        else if (DownedSurvivor && bWasDowned && !DownedSurvivor->IsDowned)
        {
            SendSurvivorActionToServer(ACTION_SURVIVOR_REVIVE_COMPLETE, DownedSurvivor);
            StopInteractingWithCurrentTarget(true);
        }
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

        // 1. ?꾩튂 諛??뚯쟾 ?명똿
        FVector CurLocation = GetActorLocation();
        MovePkt.Data.X = CurLocation.X;
        MovePkt.Data.Y = CurLocation.Y;
        MovePkt.Data.Z = CurLocation.Z;
        MovePkt.Data.RotationYaw = GetActorRotation().Yaw;

        // 2. [?섏젙??遺遺? 蹂듭옟???띾룄 怨꾩궛??吏?곌퀬, ?낅젰媛믪쓣 洹몃?濡??ｌ뒿?덈떎!
        MovePkt.Data.ForwardValue = MoveForwardValue;
        MovePkt.Data.RightValue = MoveRightValue;

        // 3. ?щ━湲??곹깭 ?명똿 (湲곗〈 肄붾뱶 ?좎?)
        MovePkt.Data.bIsSprinting = (GetCharacterMovement()->MaxWalkSpeed > 350.0f);


        // 4. ?쒕쾭濡??꾩넚
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
    // 占쏙옙占쏙옙 1000占쏙옙占쏙옙 150 占쏙옙占쏙옙占쏙옙 850 占쏙옙占쏙옙
    GetCharacterMovement()->MaxWalkSpeed = 350.0f;
}

void ATutorialCharacter::EndSprint()
{
    // 占쏙옙占쏙옙 600占쏙옙占쏙옙 150 占쏙옙占쏙옙占쏙옙 450 占쏙옙占쏙옙
    GetCharacterMovement()->MaxWalkSpeed = 350.0f;
}

void ATutorialCharacter::Turn(float Value) { AddControllerYawInput(Value); }
void ATutorialCharacter::LookUp(float Value) { AddControllerPitchInput(Value); }

void ATutorialCharacter::BeginCrouch() { Crouch(); }
void ATutorialCharacter::EndCrouch() { UnCrouch(); }


void ATutorialCharacter::TryVault()
{
    if (!CanStartVault()) return;

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

bool ATutorialCharacter::CanStartVault() const
{
    return !bIsVaulting && !IsDowned && !IsBeingCarried;
}

void ATutorialCharacter::StartVaultFromInteractable(AParkourInteractable* ParkourInteractable)
{
    if (!CanStartVault() || !ParkourInteractable || !MotionWarping)
    {
        return;
    }

    bIsVaulting = true;
    VaultAlpha = 0.0f;
    MotionWarping->AddOrUpdateWarpTargetFromLocation(FName("VaultTarget"), ParkourInteractable->GetVaultTargetLocation());

    if (VaultMontage)
    {
        PlayAnimMontage(VaultMontage);
    }
}

void ATutorialCharacter::TraceForInteractable()
{
    if (!Camera) return;

    FHitResult Hit;
    FVector StartLocation = Camera->GetComponentLocation();
    FVector ForwardVector = Camera->GetForwardVector();

    // ?ㅼ젣 議곗???理쒖쟻?붾맂 ?ш굅由ъ? ?쒖옉 吏??
    FVector TraceStart = StartLocation;
    FVector TraceEnd = TraceStart + (ForwardVector * 1500.f);

    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);

    // ?먯젙 踰붿쐞瑜??됰꼮?섍쾶 ?섏뿬 ?꾩썙?덈뒗 ??곷룄 ???≫엳?꾨줉 ?좎? (諛섏?由?40cm)
    FCollisionShape SphereShape = FCollisionShape::MakeSphere(90.f);

    TArray<FHitResult> Hits;
    GetWorld()->SweepMultiByChannel(
        Hits, TraceStart, TraceEnd, FQuat::Identity, ECC_Visibility, SphereShape, Params
    );

    AActor* NewInteractable = nullptr;

    for (const FHitResult& CandidateHit : Hits)
    {
        AActor* HitActor = CandidateHit.GetActor();
        if (!HitActor || HitActor == this)
        {
            continue;
        }

        if (!Cast<IInteractionInterface>(HitActor))
        {
            continue;
        }

        if (ATutorialCharacter* TargetChar = Cast<ATutorialCharacter>(HitActor))
        {
            if (TargetChar->IsDowned)
            {
                NewInteractable = HitActor;
                break;
            }
        }
        else
        {
            NewInteractable = HitActor;
            break;
        }
    }

    if (!NewInteractable)
    {
        TArray<AActor*> FoundSurvivors;
        UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATutorialCharacter::StaticClass(), FoundSurvivors);

        const FVector SearchOrigin = Camera->GetComponentLocation();
        const FVector SearchForward = Camera->GetForwardVector().GetSafeNormal();
        constexpr float MaxReviveInteractDistance = 500.f;
        constexpr float MinReviveFacingDot = -0.15f;

        ATutorialCharacter* BestDownedSurvivor = nullptr;
        float BestScore = TNumericLimits<float>::Max();

        for (AActor* Actor : FoundSurvivors)
        {
            ATutorialCharacter* Survivor = Cast<ATutorialCharacter>(Actor);
            if (!IsValid(Survivor) || Survivor == this || !Survivor->IsDowned || Survivor->IsBeingCarried)
            {
                continue;
            }

            FVector SurvivorTargetLocation = Survivor->GetActorLocation();
            SurvivorTargetLocation.Z += 50.0f;

            const FVector ToSurvivor = SurvivorTargetLocation - SearchOrigin;
            const float Distance = ToSurvivor.Size();
            if (Distance > MaxReviveInteractDistance)
            {
                continue;
            }

            const float FacingDot = FVector::DotProduct(SearchForward, ToSurvivor.GetSafeNormal());
            if (FacingDot < MinReviveFacingDot)
            {
                continue;
            }

            const float Score = Distance - (FacingDot * 250.f);
            if (Score < BestScore)
            {
                BestScore = Score;
                BestDownedSurvivor = Survivor;
            }
        }

        NewInteractable = BestDownedSurvivor;
    }

    if (!NewInteractable)
    {
        TArray<AActor*> FoundGenerators;
        UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGenerator::StaticClass(), FoundGenerators);

        const FVector SearchOrigin = Camera->GetComponentLocation();
        const FVector SearchForward = Camera->GetForwardVector().GetSafeNormal();
        constexpr float MaxGeneratorInteractDistance = 650.f;
        constexpr float MinGeneratorFacingDot = 0.25f;

        AGenerator* BestGenerator = nullptr;
        float BestScore = TNumericLimits<float>::Max();

        for (AActor* Actor : FoundGenerators)
        {
            AGenerator* Generator = Cast<AGenerator>(Actor);
            if (!IsValid(Generator) || Generator->bIsRepaired)
            {
                continue;
            }

            const FVector ToGenerator = Generator->GetActorLocation() - SearchOrigin;
            const float Distance = ToGenerator.Size();
            if (Distance > MaxGeneratorInteractDistance)
            {
                continue;
            }

            const float FacingDot = FVector::DotProduct(SearchForward, ToGenerator.GetSafeNormal());
            if (FacingDot < MinGeneratorFacingDot)
            {
                continue;
            }

            const float Score = Distance - (FacingDot * 200.f);
            if (Score < BestScore)
            {
                BestScore = Score;
                BestGenerator = Generator;
            }
        }

        NewInteractable = BestGenerator;
    }
    // ?곹샇?묒슜 ??곸씠 諛붾뚯뿀???뚯쓽 泥섎━
    if (CurrentInteractable != NewInteractable)
    {
        if (IsInteracting && CurrentInteractable)
        {
            AGenerator* Generator = Cast<AGenerator>(CurrentInteractable);
            ATutorialCharacter* DownedSurvivor = Cast<ATutorialCharacter>(CurrentInteractable);
            IInteractionInterface::Execute_CancelInteract(CurrentInteractable);
            IsInteracting = false;
            SetRepairingGenerator(false);
            SetRevivingSurvivor(false);

            if (Generator)
            {
                SendGeneratorActionToServer(ACTION_GENERATOR_CANCEL, Generator);
            }
            else if (DownedSurvivor)
            {
                SendSurvivorActionToServer(ACTION_SURVIVOR_REVIVE_CANCEL, DownedSurvivor);
            }
        }
        CurrentInteractable = NewInteractable;
    }
}

void ATutorialCharacter::StartInteraction()
{
    if (IsDowned || IsBeingCarried)
    {
        return;
    }

    TraceForInteractable();

    if (!CurrentInteractable)
    {
        UE_LOG(LogTemp, Warning, TEXT("No interactable found."));
        return;
    }

    if (CurrentInteractable)
    {
        if (AParkourInteractable* ParkourInteractable = Cast<AParkourInteractable>(CurrentInteractable))
        {
            StartVaultFromInteractable(ParkourInteractable);
            return;
        }
        // [異붽???濡쒖쭅] ?대? ?섎━??諛쒖쟾湲곗씤吏 ?뺤씤
        if (AGenerator* Generator = Cast<AGenerator>(CurrentInteractable))
        {
            if (Generator->bIsRepaired)
            {
                UE_LOG(LogTemp, Warning, TEXT("This generator is already done!"));
                return; // ?⑥닔 醫낅즺
            }
        }

        IInteractionInterface::Execute_StartInteract(CurrentInteractable, this);
        IsInteracting = true;

        if (AGenerator* Generator = Cast<AGenerator>(CurrentInteractable))
        {
            SetRepairingGenerator(true);
            SendGeneratorActionToServer(ACTION_GENERATOR_START, Generator);
        }
        else if (ATutorialCharacter* DownedSurvivor = Cast<ATutorialCharacter>(CurrentInteractable))
        {
            SetRevivingSurvivor(true);
            SendSurvivorActionToServer(ACTION_SURVIVOR_REVIVE_START, DownedSurvivor);
        }
    }
}

void ATutorialCharacter::CancelInteraction()
{
    if (IsInteracting && CurrentInteractable)
    {
        AGenerator* Generator = Cast<AGenerator>(CurrentInteractable);
        ATutorialCharacter* DownedSurvivor = Cast<ATutorialCharacter>(CurrentInteractable);
        IInteractionInterface::Execute_CancelInteract(CurrentInteractable);
        IsInteracting = false;
        SetRepairingGenerator(false);
        SetRevivingSurvivor(false);

        if (Generator)
        {
            SendGeneratorActionToServer(ACTION_GENERATOR_CANCEL, Generator);
        }
        else if (DownedSurvivor)
        {
            SendSurvivorActionToServer(ACTION_SURVIVOR_REVIVE_CANCEL, DownedSurvivor);
        }
    }
}


void ATutorialCharacter::SetRepairingGenerator(bool bRepairing)
{
    if (bIsRepairingGenerator == bRepairing)
    {
        return;
    }

    bIsRepairingGenerator = bRepairing;

    if (bIsRepairingGenerator)
    {
        PlayRepairMontageStart();
    }
    else
    {
        PlayRepairMontageEnd();
    }
}
void ATutorialCharacter::SendGeneratorActionToServer(uint8 ActionType, AGenerator* Generator)
{
    if (!Generator || !NetworkWorker || !NetworkWorker->GetSocket() || MyPlayerId == -1) return;

    FPacketAction ActionPkt;
    ActionPkt.Type = PKT_ACTION;
    ActionPkt.ActionType = ActionType;
    ActionPkt.InstigatorId = MyPlayerId;
    ActionPkt.TargetId = Generator->GetGeneratorId();

    const FVector Loc = Generator->GetActorLocation();
    ActionPkt.X = Loc.X;
    ActionPkt.Y = Loc.Y;
    ActionPkt.Z = Loc.Z;
    ActionPkt.RotationYaw = Generator->GetRepairProgress();

    int32 BytesSent = 0;
    NetworkWorker->GetSocket()->Send((uint8*)&ActionPkt, sizeof(FPacketAction), BytesSent);
}

void ATutorialCharacter::SendSurvivorActionToServer(uint8 ActionType, ATutorialCharacter* TargetCharacter)
{
    if (!TargetCharacter || !NetworkWorker || !NetworkWorker->GetSocket() || MyPlayerId == -1) return;

    FPacketAction ActionPkt;
    ActionPkt.Type = PKT_ACTION;
    ActionPkt.ActionType = ActionType;
    ActionPkt.InstigatorId = MyPlayerId;
    ActionPkt.TargetId = TargetCharacter->MyPlayerId;

    const FVector Loc = TargetCharacter->GetActorLocation();
    ActionPkt.X = Loc.X;
    ActionPkt.Y = Loc.Y;
    ActionPkt.Z = Loc.Z;
    ActionPkt.RotationYaw = GetActorRotation().Yaw;

    int32 BytesSent = 0;
    NetworkWorker->GetSocket()->Send((uint8*)&ActionPkt, sizeof(FPacketAction), BytesSent);
}

void ATutorialCharacter::ShowGeneratorRepairCount() const
{
    UWorld* World = GetWorld();
    if (!World) return;

    TArray<AActor*> FoundGenerators;
    UGameplayStatics::GetAllActorsOfClass(World, AGenerator::StaticClass(), FoundGenerators);

    int32 TotalGenerators = 0;
    int32 RepairedGenerators = 0;

    for (AActor* Actor : FoundGenerators)
    {
        AGenerator* Generator = Cast<AGenerator>(Actor);
        if (!Generator) continue;

        ++TotalGenerators;
        if (Generator->bIsRepaired)
        {
            ++RepairedGenerators;
        }
    }

    const FString Message = FString::Printf(TEXT("Generator Repaired: %d/%d"), TotalGenerators, RepairedGenerators);
    UE_LOG(LogTemp, Warning, TEXT("%s"), *Message);

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(3001, 4.0f, FColor::Yellow, Message);
    }
}
AGenerator* ATutorialCharacter::FindGeneratorForNetworkAction(int32 GeneratorId, const FVector& Location) const
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

void ATutorialCharacter::ApplyGeneratorNetworkAction(uint8 ActionType, int32 GeneratorId, const FVector& Location, float RepairProgress)
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
        const bool bWasRepaired = Generator->bIsRepaired;
        Generator->ApplyNetworkRepairState(false, true, 1.f);
        if (!bWasRepaired)
        {
            ShowGeneratorRepairCount();
        }
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
    if (IsInteracting)
    {
        CancelInteraction();
    }

    CurrentHealth = 0;
    IsDowned = true;
    bIsBeingRevived = false;
    RecoveryProgress = 0.0f;
    CurrentReviver = nullptr;
    bCanBeHit = false;

    if (DownedMontage)
    {
        PlayAnimMontage(DownedMontage);
    }
    else if (DownedAnimation)
    {
        PlayLoopBodyAnimation(DownedAnimation);
    }

    GetCapsuleComponent()->SetCapsuleHalfHeight(30.0f);
    GetCharacterMovement()->DisableMovement();
    bUseControllerRotationYaw = false;

    UE_LOG(LogTemp, Error, TEXT("Survivor entered the downed state."));
}
void ATutorialCharacter::ApplyHitReaction(bool bRespectCooldown)
{
    if (IsDowned) return;
    if (bRespectCooldown && !bCanBeHit) return;

    bCanBeHit = false;
    CurrentHealth--;
    UE_LOG(LogTemp, Warning, TEXT("Survivor took damage. Current health: %d"), CurrentHealth);

    if (CurrentHealth > 0)
    {
        if (HitMontage)
        {
            PlayAnimMontage(HitMontage);
        }
        else if (HitReactionAnimation)
        {
            PlayTemporaryBodyAnimation(HitReactionAnimation);
        }

        FTimerHandle HitCooldownTimer;
        GetWorldTimerManager().SetTimer(HitCooldownTimer, FTimerDelegate::CreateLambda([this]()
            {
                bCanBeHit = true;
                UE_LOG(LogTemp, Log, TEXT("占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙 占쌕쏙옙 占쏙옙占쏙옙 占쏙옙 占쏙옙占쏙옙"));
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

    // 1. 占십울옙 占쌔댐옙 ID占쏙옙 占쌍댐옙占쏙옙 확占쏙옙
    if (RemotePlayers.Contains(PlayerId))
    {
        // 占쏙옙占쏙옙占싹곤옙 캐占쏙옙占싶뤄옙 占쏙옙占쏙옙환
        ATutorialCharacter* Target = Cast<ATutorialCharacter>(RemotePlayers[PlayerId]);

        // [占쏙옙占쏙옙] Target占쏙옙 占쌨모리울옙 占쏙옙占쏙옙殮綬?占싹몌옙 占쏙옙占쏙옙占쏙옙트 占쏙옙占쏙옙
        if (IsValid(Target))
        {
            Target->SetActorLocation(Location);
            Target->SetActorRotation(FRotator(0.0f, RotationYaw, 0.0f));

            Target->RemoteForwardValue = Forward;
            Target->RemoteRightValue = Right;
            Target->RemoteIsSprinting = bSprint;

            // 占쏙옙占썩서 占쌉쇽옙 占쏙옙占쏙옙 (占쏙옙占쏙옙占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙트占쏙옙)
            return;
        }
        else
        {
            // 占쏙옙占쏙옙占쏙옙 占시뤄옙占쏙옙 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙占쏙옙摸占?占십울옙占쏙옙 占쏙옙占쏙옙
            RemotePlayers.Remove(PlayerId);
        }
    }

    // 2. 占십울옙 占쏙옙占신놂옙 Target占쏙옙 占쏙옙효占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙荑∽옙占?占쏙옙占쏙옙 (占쏙옙占썩가 else 占쏙옙占쏙옙 占쏙옙占쏙옙 占쏙옙)
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    ATutorialCharacter* NewPlayer = World->SpawnActor<ATutorialCharacter>(GetClass(), Location, FRotator(0.0f, RotationYaw, 0.0f), SpawnParams);

    if (NewPlayer)
    {
        NewPlayer->MyPlayerId = PlayerId;
        NewPlayer->AutoPossessPlayer = EAutoReceiveInput::Disabled;

        // [?섏젙] NoCollision(異⑸룎 ?놁쓬)??QueryOnly(?덉씠? 媛먯?留?媛??濡?諛붽퓠?덈떎.
        // ?대젃寃??댁빞 ?덉씠?(Trace)媛 罹먮┃?곗쓽 紐몄뿉 留욎뒿?덈떎.
        NewPlayer->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

        // [異붽?] ?뱀떆 紐⑤Ⅴ???덉씠? 梨꾨꼸(Visibility)???뺤떎??'Block'?섎룄濡??ㅼ젙?⑸땲??
        NewPlayer->GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

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
            // [?듭떖 異붽?] ?쒕쾭?먯꽌 諛쏆? ?좊땲硫붿씠???낅젰媛믪쓣 ?щ윭?먭쾶 二쇱엯!
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
        // [?듭떖 異붽?] 泥섏쓬 ?ㅽ룿???뚮룄 珥덇린 ?대룞 媛믪쓣 ?ｌ뼱以띾땲??
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
    if (ActionType == ACTION_GENERATOR_START || ActionType == ACTION_GENERATOR_CANCEL || ActionType == ACTION_GENERATOR_COMPLETE)
    {
        if (RemotePlayers.Contains(InstigatorId) && IsValid(RemotePlayers[InstigatorId]))
        {
            RemotePlayers[InstigatorId]->SetRepairingGenerator(ActionType == ACTION_GENERATOR_START);
            RemotePlayers[InstigatorId]->IsInteracting = (ActionType == ACTION_GENERATOR_START);
        }

        ApplyGeneratorNetworkAction(ActionType, TargetId, Location, RotationYaw);
        return;
    }

    if (ActionType == ACTION_SURVIVOR_REVIVE_START || ActionType == ACTION_SURVIVOR_REVIVE_CANCEL || ActionType == ACTION_SURVIVOR_REVIVE_COMPLETE)
    {
        ATutorialCharacter* Reviver = nullptr;
        if (InstigatorId == MyPlayerId)
        {
            Reviver = this;
        }
        else if (RemotePlayers.Contains(InstigatorId) && IsValid(RemotePlayers[InstigatorId]))
        {
            Reviver = RemotePlayers[InstigatorId];
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
                Survivor->CurrentReviver = Reviver;
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
                Survivor->CurrentReviver = nullptr;
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

void ATutorialCharacter::PlayRepairMontageStart()
{
    UAnimInstance* AnimInstance = GetMesh() ? GetMesh()->GetAnimInstance() : nullptr;
    if (RepairMontage && AnimInstance)
    {
        const bool bIsAlreadyPlaying = AnimInstance->Montage_IsPlaying(RepairMontage);
        if (!bIsAlreadyPlaying)
        {
            AnimInstance->Montage_Play(RepairMontage);
        }

        AnimInstance->Montage_JumpToSection(FName(TEXT("Start")), RepairMontage);
        return;
    }

    if (RepairAnimation)
    {
        PlayLoopBodyAnimation(RepairAnimation);
    }
}

void ATutorialCharacter::PlayRepairMontageEnd()
{
    UAnimInstance* AnimInstance = GetMesh() ? GetMesh()->GetAnimInstance() : nullptr;
    if (RepairMontage && AnimInstance && AnimInstance->Montage_IsPlaying(RepairMontage))
    {
        AnimInstance->Montage_JumpToSection(FName(TEXT("End")), RepairMontage);
        return;
    }

    RestoreBodyAnimClass();
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

void ATutorialCharacter::SetRevivingSurvivor(bool bReviving)
{
    if (bReviving)
    {
        if (RepairAnimation)
        {
            PlayLoopBodyAnimation(RepairAnimation);
        }
    }
    else if (!bIsRepairingGenerator)
    {
        RestoreBodyAnimClass();
    }
}

void ATutorialCharacter::StopInteractingWithCurrentTarget(bool bRestoreAnimation)
{
    IsInteracting = false;
    SetRepairingGenerator(false);

    if (bRestoreAnimation)
    {
        SetRevivingSurvivor(false);
    }
}

// 1. ?곹샇?묒슜 ?쒖옉
void ATutorialCharacter::StartInteract_Implementation(ACharacter* Interactor)
{
    if (!IsDowned || IsBeingCarried || !Interactor) return;

    ATutorialCharacter* Reviver = Cast<ATutorialCharacter>(Interactor);
    if (!Reviver || Reviver == this) return;

    CurrentReviver = Reviver;
    bIsBeingRevived = true;
    RecoveryProgress = 0.0f;
    UE_LOG(LogTemp, Warning, TEXT("Someone is healing me!"));
}

// 2. ?곹샇?묒슜 ?낅뜲?댄듃 (吏꾪뻾)
void ATutorialCharacter::UpdateInteract_Implementation(float DeltaTime)
{
    if (!IsDowned || !CurrentReviver.IsValid()) return;

    RecoveryProgress += DeltaTime / MaxRecoveryTime;
    RecoveryProgress = FMath::Clamp(RecoveryProgress, 0.f, 1.f);

    // GEngine->AddOnScreenDebugMessage(...) ??젣

    if (RecoveryProgress >= 1.0f)
    {
        IInteractionInterface::Execute_CompleteInteract(this);
    }
}

// 3. ?곹샇?묒슜 痍⑥냼
void ATutorialCharacter::CancelInteract_Implementation()
{
    bIsBeingRevived = false;
    RecoveryProgress = 0.0f;
    CurrentReviver = nullptr;
    UE_LOG(LogTemp, Warning, TEXT("Healing interrupted."));
}

// 4. ?곹샇?묒슜 ?꾨즺 (遺??
void ATutorialCharacter::CompleteInteract_Implementation()
{
    if (!IsDowned) return;

    IsDowned = false;
    IsBeingCarried = false;
    bIsBeingRevived = false;
    CurrentHealth = 1; // 遺???곹깭濡?蹂듦뎄
    RecoveryProgress = 0.0f;
    DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

    // 罹≪뒓 ?믪씠? ?대룞 ?λ젰 蹂듦뎄
    GetCapsuleComponent()->SetCapsuleHalfHeight(88.0f);
    GetCharacterMovement()->SetDefaultMovementMode();
    GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    bCanBeHit = true;
    CurrentReviver = nullptr;

    // ?좊땲硫붿씠??蹂듦뎄 濡쒖쭅 ?몄텧
    RestoreBodyAnimClass();

    UE_LOG(LogTemp, Warning, TEXT("Survivor has been revived!"));
}

float ATutorialCharacter::GetInteractDuration_Implementation() const
{
    return MaxRecoveryTime;
}

