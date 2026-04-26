#include "MyProject_Start/Player/TutorialCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "MyProject_Start/InteractionInterface.h"
#include "MyProject_Start/NetworkWorker.h" // ??
#include "MyProject_Start/KillerCharacter.h"
#include "Networking.h"    // ??
#include "Sockets.h"       // ??
ATutorialCharacter::ATutorialCharacter()
{
    bCanVault = false;
    PrimaryActorTick.bCanEverTick = true;
    // ??? ? ???? ??
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
    // ?? ?? ? ?? ??
    GetMesh()->SetRelativeLocationAndRotation(
        FVector(0.f, 0.f, -88.f),
        FRotator(0.f, -90.f, 0.f)
    );
    static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(
        TEXT("/Script/Engine.SkeletalMesh'/Game/Animation/Walking.Walking'")
    );
    if (SM.Succeeded())
    {
        GetMesh()->SetSkeletalMesh(SM.Object);
    }
    // ?? ??
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
    if (IsPlayerControlled() && IsLocallyControlled())
    {
        RemotePlayers.Empty();
    }
    if (IsPlayerControlled() && IsLocallyControlled())
    {
        NetworkWorker = new FNetworkWorker(TEXT("127.0.0.1"), 7777);
        NetworkWorker->SetOwnerCharacter(this);
        FRunnableThread::Create(NetworkWorker, TEXT("NetworkThread"));
    }
}
void ATutorialCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    // ?? ?? ? ???? ???? ??
    if (NetworkWorker)
    {
        NetworkWorker->Stop();
        // ??? ??? ????? ???
    }
    Super::EndPlay(EndPlayReason);
    ATutorialCharacter::RemotePlayers.Empty();
    ATutorialCharacter::RemoteKillers.Empty();
}
void ATutorialCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    TraceForInteractable();
    // ? ???? ???? ??? ?? ??
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
        // ?? ??
        FVector CurLocation = GetActorLocation();
        MovePkt.Data.X = CurLocation.X;
        MovePkt.Data.Y = CurLocation.Y;
        MovePkt.Data.Z = CurLocation.Z;
        MovePkt.Data.RotationYaw = GetActorRotation().Yaw;
        FVector Velocity2D = GetVelocity();
        Velocity2D.Z = 0.0f;
        if (Velocity2D.SizeSquared() > 1.0f)
        {
            const FVector MoveDir = Velocity2D.GetSafeNormal();
            FVector ActorForward = GetActorForwardVector();
            FVector ActorRight = GetActorRightVector();
            ActorForward.Z = 0.0f;
            ActorRight.Z = 0.0f;
            MovePkt.Data.ForwardValue = FVector::DotProduct(MoveDir, ActorForward.GetSafeNormal());
            MovePkt.Data.RightValue = FVector::DotProduct(MoveDir, ActorRight.GetSafeNormal());
        }
        else
        {
            MovePkt.Data.ForwardValue = 0.0f;
            MovePkt.Data.RightValue = 0.0f;
        }
        MovePkt.Data.bIsSprinting = (GetCharacterMovement()->MaxWalkSpeed > 600.0f);
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
    // ?? 1000?? 150 ??? 850 ??
    GetCharacterMovement()->MaxWalkSpeed = 850.0f;
}
void ATutorialCharacter::EndSprint()
{
    // ?? 600?? 150 ??? 450 ??
    GetCharacterMovement()->MaxWalkSpeed = 450.0f;
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
    if (!Camera) return; // ???? ??? ?? ? ?
    FHitResult Hit;
    // 1. ???? ?? ?? ??? ?? ??? ?????.
    FVector StartLocation = Camera->GetComponentLocation();
    FVector ForwardVector = Camera->GetForwardVector();
    // 2. ???(Start)? ??? ? ??? 1?? ?? ?????. (?? ?? ?? ??)
    FVector TraceStart = StartLocation + (ForwardVector * 100.f);
    // 3. ??(End)? ????? 300 unit(3??) ? ??? ?????.
    FVector TraceEnd = TraceStart + (ForwardVector * 300.f);
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this); // ??(??? ??) ??
    // 4. LineTrace ??
    bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_Visibility, Params);
    AActor* NewInteractable = nullptr;
    if (bHit && Hit.GetActor() && Hit.GetActor()->Implements<UInteractionInterface>())
    {
        NewInteractable = Hit.GetActor();
    }
    // ??? ???? ???? ???? Cancel ??
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
    // 1. ?? ?????, '?? ???' ???? ?? ?? ? ?
    if (IsDowned || !bCanBeHit) return;
    // 2. ?? ???? ?? ?? ??? ??
    bCanBeHit = false;
    // 3. ?? ?? ? ??
    CurrentHealth--;
    UE_LOG(LogTemp, Warning, TEXT("??? ???! ?? ??: %d"), CurrentHealth);
    // 4. ??? ?? ?? ??
    if (CurrentHealth > 0)
    {
        if (HitMontage)
        {
            PlayAnimMontage(HitMontage);
        }
        // --- ?? ?? ??? ?? ---
        // ???? ?? ??? ??? ?? ???(? 0.5?~0.8?) ?? ? ?? ??
        FTimerHandle HitCooldownTimer;
        GetWorldTimerManager().SetTimer(HitCooldownTimer, FTimerDelegate::CreateLambda([this]()
            {
                bCanBeHit = true;
                UE_LOG(LogTemp, Log, TEXT("??? ?? ?? ?? ? ??"));
            }), 1.0f, false);
        // --------------------------
    }
    else
    {
        // ? ?? ??: ??(??)
        IsDowned = true;
        if (DownedMontage)
        {
            PlayAnimMontage(DownedMontage);
        }
        GetCapsuleComponent()->SetCapsuleHalfHeight(30.0f);
        GetCharacterMovement()->DisableMovement();
        bUseControllerRotationYaw = false;
        UE_LOG(LogTemp, Error, TEXT("??? ?? ??(Downed)!"));
    }
}
void ATutorialCharacter::UpdateRemotePlayer(int32 PlayerId, FVector Location, float RotationYaw, float Forward, float Right, bool bSprint)
{
    UWorld* World = GetWorld();
    if (!World || World->bIsTearingDown) return;
    if (!IsValid(this)) return;
    // [??] ??? ID(0?)? ? ??? ???? ????? ??? ???? ??? ??? ???.
    if (PlayerId == 0)
    {
        UpdateRemoteKiller(PlayerId, Location, RotationYaw, Forward, Right, bSprint);
        return;
    }
    // 1. ?? ?? ID? ??? ??
    if (RemotePlayers.Contains(PlayerId))
    {
        // ??: Cast ?? ?? ??? ???? ???? ?????.
        AActor* FoundActor = RemotePlayers[PlayerId];
        if (IsValid(FoundActor))
        {
            // ??? ??? ??
            ATutorialCharacter* Target = Cast<ATutorialCharacter>(FoundActor);
            // ??? ?? (?? ??? ??? ??)
            if (Target)
            {
                Target->SetActorLocation(Location);
                Target->SetActorRotation(FRotator(0.0f, RotationYaw, 0.0f));
                Target->RemoteForwardValue = Forward;
                Target->RemoteRightValue = Right;
                Target->RemoteIsSprinting = bSprint;
                Target->SetActorHiddenInGame(false);
                Target->GetMesh()->SetHiddenInGame(false, true);
                Target->GetMesh()->SetVisibility(true, true);
                Target->GetMesh()->SetOwnerNoSee(false);
                Target->GetMesh()->SetOnlyOwnerSee(false);
                return;
            }
            else
            {
                // ??? ??: ??? ????? ?? ???? ?? ???? ???? ????.
                UE_LOG(LogTemp, Error, TEXT("ID %d: Cast Failed! This actor is not a Survivor."), PlayerId);
                RemotePlayers.Remove(PlayerId); // ??? ??? ??
            }
        }
        else
        {
            RemotePlayers.Remove(PlayerId);
        }
    }
    // 2. ??? ???? ?? ??
    UClass* ClassToSpawn = nullptr;
    if (PlayerId == 0)
    {
        // KillerClass? ??? ? ?? ????, ??? ?? ??? ??
        ClassToSpawn = KillerBPClass ? *KillerBPClass : GetClass();
    }
    else
    {
        ClassToSpawn = SurvivorBPClass ? *SurvivorBPClass : GetClass();
    }
    // 2. ?? ???? ??
    FActorSpawnParameters SpawnParams;
    // Remote proxy actors should not inherit local owner visibility rules.
    SpawnParams.Owner = nullptr;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    // 3. ??? ClassToSpawn?? ??
    ATutorialCharacter* NewPlayer = World->SpawnActor<ATutorialCharacter>(ClassToSpawn, Location, FRotator(0.0f, RotationYaw, 0.0f), SpawnParams);
    if (NewPlayer)
    {
        NewPlayer->MyPlayerId = PlayerId;
        NewPlayer->AutoPossessPlayer = EAutoReceiveInput::Disabled;
        NewPlayer->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        NewPlayer->SetActorHiddenInGame(false);
        NewPlayer->GetMesh()->SetHiddenInGame(false, true);
        NewPlayer->GetMesh()->SetVisibility(true, true);
        NewPlayer->GetMesh()->SetOwnerNoSee(false);
        NewPlayer->GetMesh()->SetOnlyOwnerSee(false);
        NewPlayer->DisableInput(nullptr);
        RemotePlayers.Add(PlayerId, NewPlayer);
        UE_LOG(LogTemp, Warning, TEXT("%s Spawned! ID: %d"), (PlayerId == 0 ? TEXT("Killer") : TEXT("Survivor")), PlayerId);
    }
}
void ATutorialCharacter::UpdateRemoteKiller(int32 PlayerId, FVector Location, float RotationYaw, float Forward, float Right, bool bSprint)
{
    UWorld* World = GetWorld();
    if (!World || World->bIsTearingDown) return;
    if (RemoteKillers.Contains(PlayerId))
    {
        AKillerCharacter* Target = RemoteKillers[PlayerId];
        if (IsValid(Target))
        {
            Target->SetActorLocation(Location);
            Target->SetActorRotation(FRotator(0.0f, RotationYaw, 0.0f));
            Target->SetRemoteForwardValue(Forward);
            Target->SetRemoteRightValue(Right);
            Target->SetRemoteMovementSpeed(FVector(Forward, Right, 0.0f).Size() * 600.0f);
            Target->SetActorHiddenInGame(false);
            Target->GetMesh()->SetHiddenInGame(false, true);
            Target->GetMesh()->SetVisibility(true, true);
            Target->GetMesh()->SetOwnerNoSee(false);
            Target->GetMesh()->SetOnlyOwnerSee(false);
            return;
        }
        RemoteKillers.Remove(PlayerId);
    }
    // [??] C++ ???? ?? ????? ??? KillerBPClass? ?????.
    UClass* ClassToSpawn = KillerBPClass ? *KillerBPClass : AKillerCharacter::StaticClass();
    FActorSpawnParameters SpawnParams;
    // Remote proxy actors should not inherit local owner visibility rules.
    SpawnParams.Owner = nullptr;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    AKillerCharacter* NewKiller = World->SpawnActor<AKillerCharacter>(ClassToSpawn, Location, FRotator(0.0f, RotationYaw, 0.0f), SpawnParams);
    if (NewKiller)
    {
        NewKiller->MyPlayerId = PlayerId;
        NewKiller->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        NewKiller->SetRemoteForwardValue(Forward);
        NewKiller->SetRemoteRightValue(Right);
        NewKiller->SetRemoteMovementSpeed(FVector(Forward, Right, 0.0f).Size() * 600.0f);
        NewKiller->SetActorHiddenInGame(false);
        NewKiller->GetMesh()->SetHiddenInGame(false, true);
        NewKiller->GetMesh()->SetVisibility(true, true);
        NewKiller->GetMesh()->SetOwnerNoSee(false);
        NewKiller->GetMesh()->SetOnlyOwnerSee(false);
        RemoteKillers.Add(PlayerId, NewKiller);
        UE_LOG(LogTemp, Warning, TEXT("Killer Blueprint Spawned! ID: %d"), PlayerId);
    }
}
void ATutorialCharacter::SwitchToKillerClass()
{
    UWorld* World = GetWorld();
    if (!World) return;
    // 1. ?? ? ??? ??? ??
    FVector SpawnLocation = GetActorLocation();
    FRotator SpawnRotation = GetActorRotation();
    // 2. ?? ?? ?? ?? ???? ????
    APlayerController* PC = Cast<APlayerController>(GetController());
    if (!PC) return;
    // 3. ??? ????? ???? ???? ??? ??
    // (????? KillerBPClass ??? ??? BP? ?????? ???)
    UClass* ClassToSpawn = KillerBPClass ? *KillerBPClass : AKillerCharacter::StaticClass();
    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = nullptr; // ? ???? ???? ???? ??
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    // 4. ??? ??? ??? ?? (?? ?? ????? ????? ??? ?????)
    AKillerCharacter* NewKiller = World->SpawnActorDeferred<AKillerCharacter>(
        ClassToSpawn, FTransform(SpawnRotation, SpawnLocation), nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
    if (NewKiller)
    {
        NewKiller->NetworkWorker = NetworkWorker;
        NewKiller->MyPlayerId = MyPlayerId;

        if (NetworkWorker)
        {
            NetworkWorker->SetOwnerKiller(NewKiller);
            NetworkWorker = nullptr;
        }

        NewKiller->FinishSpawning(FTransform(SpawnRotation, SpawnLocation));
        PC->Possess(NewKiller);

        this->Destroy();
    }
}
