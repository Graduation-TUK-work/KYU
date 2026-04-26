#include "KillerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimInstance.h"
#include "DrawDebugHelpers.h"
#include "MyProject_Start/Player/TutorialCharacter.h"
#include "MyProject_Start/NetworkWorker.h"
#include "Networking.h"
#include "Sockets.h"
TMap<int32, AKillerCharacter*> AKillerCharacter::RemoteKillers;
TMap<int32, ATutorialCharacter*> AKillerCharacter::RemoteSurvivors;
// Sets default values
AKillerCharacter::AKillerCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
    // ??? ??
    FPSCamerComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
    FPSCamerComponent->SetupAttachment(GetCapsuleComponent());
    FPSCamerComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
    FPSCamerComponent->bUsePawnControlRotation = true;
    // 1?? ? ?? ??
    FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
    FPSMesh->SetOnlyOwnerSee(true);
    FPSMesh->SetupAttachment(FPSCamerComponent);
    FPSMesh->bCastDynamicShadow = false;
    FPSMesh->CastShadow = false;
    // ?? ??? ??? ??? ?? ?? (??? ??)
    FPSMesh->BoundsScale = 5.0f;
    // 3?? ??? ???? ??? ?? ??
    GetMesh()->SetOwnerNoSee(true);
    // ?? ?? ?? ???
    bIsAttacking = false;
    NetworkWorker = nullptr;
}
void AKillerCharacter::BeginPlay()
{
    Super::BeginPlay();
    if (IsPlayerControlled() && IsLocallyControlled())
    {
        RemoteKillers.Empty();
        RemoteSurvivors.Empty();

        if (NetworkWorker)
        {
            NetworkWorker->SetOwnerKiller(this);
        }
        else
        {
            NetworkWorker = new FNetworkWorker(TEXT("127.0.0.1"), 7777);
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
    AKillerCharacter::RemoteKillers.Empty();
    AKillerCharacter::RemoteSurvivors.Empty();
}
void AKillerCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    // 1. ?? ?? ?? ?? (XY ???? ??? ??)
    FVector Velocity = GetVelocity();
    FVector LateralVelocity = FVector(Velocity.X, Velocity.Y, 0.f);
    MovementSpeed = LateralVelocity.Size();
    if (IsPlayerControlled() && IsLocallyControlled())
    {
        SendLocationToServer();

        int32 ValidRemoteSurvivorCount = 0;
        for (const TPair<int32, ATutorialCharacter*>& Pair : RemoteSurvivors)
        {
            ATutorialCharacter* RemoteSurvivor = Pair.Value;
            if (!IsValid(RemoteSurvivor))
            {
                continue;
            }

            ++ValidRemoteSurvivorCount;

            const FVector MarkerLocation = RemoteSurvivor->GetActorLocation() + FVector(0.0f, 0.0f, 100.0f);
            DrawDebugSphere(GetWorld(), MarkerLocation, 20.0f, 12, FColor::Cyan, false, 0.1f, 0, 1.5f);

            if (GEngine)
            {
                const FString DebugText = FString::Printf(
                    TEXT("RemoteSurvivor[%d] Hidden=%d MeshVisible=%d Loc=(%.0f, %.0f, %.0f)"),
                    Pair.Key,
                    RemoteSurvivor->IsHidden(),
                    RemoteSurvivor->GetMesh() && RemoteSurvivor->GetMesh()->IsVisible() ? 1 : 0,
                    RemoteSurvivor->GetActorLocation().X,
                    RemoteSurvivor->GetActorLocation().Y,
                    RemoteSurvivor->GetActorLocation().Z);

                GEngine->AddOnScreenDebugMessage(
                    1000 + Pair.Key,
                    0.12f,
                    FColor::Cyan,
                    DebugText);
            }
        }

        if (GEngine)
        {
            const FString CountText = FString::Printf(TEXT("RemoteSurvivorCount=%d"), ValidRemoteSurvivorCount);
            GEngine->AddOnScreenDebugMessage(999, 0.12f, FColor::Green, CountText);
        }
    }
}
void AKillerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    // ?? ? ?? ??
    PlayerInputComponent->BindAxis("MoveForward", this, &AKillerCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AKillerCharacter::MoveRight);
    PlayerInputComponent->BindAxis("TurnCamera", this, &AKillerCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAxis("LookUp", this, &AKillerCharacter::AddControllerPitchInput);
    // ?? ?? ??? (???? ?? - ??? "Attack"? ???? ??? ???)
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
// --- ?? ?? ---
void AKillerCharacter::StartAttack()
{
    // ?? ?? ?? ?? ?? ??
    if (!bIsAttacking && AttackMontage)
    {
        UAnimInstance* AnimInstance = FPSMesh->GetAnimInstance();
        if (AnimInstance)
        {
            AnimInstance->Montage_Play(AttackMontage);
            bIsAttacking = true;
            bHasDealtDamage = false;
            GetCharacterMovement()->MaxWalkSpeed = 200.0f;
        }
        UE_LOG(LogTemp, Warning, TEXT("StartAttack called"));
    }
}
// ? ??? ??? ????? ????(Notify)?? ??? ?????.
void AKillerCharacter::EndAttack()
{
    bIsAttacking = false;
    // ?? ?? ??? ??
    GetCharacterMovement()->MaxWalkSpeed = 600.0f;
    UE_LOG(LogTemp, Warning, TEXT("EndAttack called"));
}
void AKillerCharacter::CheckHit()
{
    // [??] ?? ?? ?????? ???? ???? ??? ?? ?? (?? ?? ??)
    if (bHasDealtDamage) return;
    FVector Start = FPSCamerComponent->GetComponentLocation();
    FVector ForwardVector = FPSCamerComponent->GetForwardVector();
    FVector End = Start + (ForwardVector * AttackRange);
    FHitResult HitResult;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);
    bool bHit = GetWorld()->LineTraceSingleByChannel(
        HitResult, Start, End, ECC_Pawn, Params
    );
    DrawDebugLine(GetWorld(), Start, End, bHit ? FColor::Green : FColor::Red, false, 1.0f, 0, 2.0f);
    if (bHit && HitResult.GetActor())
    {
        ATutorialCharacter* Victim = Cast<ATutorialCharacter>(HitResult.GetActor());
        if (Victim)
        {
            // [??] ?? ?? ? ???? true? ???? ?? ?? ?? ??
            bHasDealtDamage = true;
            // ??? ?? ?? ??
            Victim->PlayHitReaction();
            UE_LOG(LogTemp, Warning, TEXT("Hit Target: %s"), *Victim->GetName());
            DrawDebugSphere(GetWorld(), HitResult.Location, 10.0f, 12, FColor::Yellow, false, 1.0f);
        }
    }
    UE_LOG(LogTemp, Warning, TEXT("CheckHit called | bHasDealtDamage = %s"), bHasDealtDamage ? TEXT("true") : TEXT("false"));
}
// ??? ?? ??
void AKillerCharacter::PickupSurvivor()
{
    if (CarriedSurvivor) return;
    FVector Start = FPSCamerComponent->GetComponentLocation();
    FVector End = Start + (FPSCamerComponent->GetForwardVector() * AttackRange);
    FHitResult Hit;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);
    if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Pawn, Params))
    {
        ATutorialCharacter* Target = Cast<ATutorialCharacter>(Hit.GetActor());
        if (Target && Target->IsDowned)
        {
            CarriedSurvivor = Target;
            // --- [??? ??!] ????? ?? ???? ?? ---
            CarriedSurvivor->IsBeingCarried = true;
            // ------------------------------------------------
            // 1. ???? ?? ? ?? ??
            CarriedSurvivor->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
            CarriedSurvivor->GetCharacterMovement()->DisableMovement();
            // 2. ???? ??? ??? ??
            CarriedSurvivor->AttachToComponent(GetMesh(),
                FAttachmentTransformRules::SnapToTargetNotIncludingScale,
                FName("CarrySocket"));
            UE_LOG(LogTemp, Warning, TEXT("???? ?????!"));
            if (PickupMontage) PlayAnimMontage(PickupMontage);
        }
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
        MovePkt.Data.CharacterType = CHARACTER_KILLER;
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
            Target->RemoteMovementSpeed = FVector(Forward, Right, 0.0f).Size() * 600.0f;
            Target->SetActorHiddenInGame(false);
            Target->GetMesh()->SetHiddenInGame(false, true);
            Target->GetMesh()->SetVisibility(true, true);
            Target->GetMesh()->SetOwnerNoSee(false);
            Target->GetMesh()->SetOnlyOwnerSee(false);
            return;
        }
        RemoteKillers.Remove(PlayerId);
    }
    FActorSpawnParameters SpawnParams;
    // Remote proxy actors should not inherit local owner visibility rules.
    SpawnParams.Owner = nullptr;
    AKillerCharacter* NewKiller = World->SpawnActor<AKillerCharacter>(
        KillerBPClass ? *KillerBPClass : AKillerCharacter::StaticClass(),
        Location,
        FRotator(0.0f, RotationYaw, 0.0f),
        SpawnParams);
    if (NewKiller)
    {
        NewKiller->MyPlayerId = PlayerId;
        NewKiller->AutoPossessPlayer = EAutoReceiveInput::Disabled;
        NewKiller->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        NewKiller->RemoteForwardValue = Forward;
        NewKiller->RemoteRightValue = Right;
        NewKiller->RemoteMovementSpeed = FVector(Forward, Right, 0.0f).Size() * 600.0f;
        NewKiller->SetActorHiddenInGame(false);
        NewKiller->GetMesh()->SetHiddenInGame(false, true);
        NewKiller->GetMesh()->SetVisibility(true, true);
        NewKiller->GetMesh()->SetOwnerNoSee(false);
        NewKiller->GetMesh()->SetOnlyOwnerSee(false);
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
            Target->SetActorHiddenInGame(false);
            Target->GetMesh()->SetHiddenInGame(false, true);
            Target->GetMesh()->SetVisibility(true, true);
            Target->GetMesh()->SetOwnerNoSee(false);
            Target->GetMesh()->SetOnlyOwnerSee(false);
            return;
        }
        RemoteSurvivors.Remove(PlayerId);
    }
    FActorSpawnParameters SpawnParams;
    // Remote proxy actors should not inherit local owner visibility rules.
    SpawnParams.Owner = nullptr;
    ATutorialCharacter* NewSurvivor = World->SpawnActor<ATutorialCharacter>(
        SurvivorBPClass ? *SurvivorBPClass : ATutorialCharacter::StaticClass(),
        Location,
        FRotator(0.0f, RotationYaw, 0.0f),
        SpawnParams);
    if (NewSurvivor)
    {
        NewSurvivor->MyPlayerId = PlayerId;
        NewSurvivor->AutoPossessPlayer = EAutoReceiveInput::Disabled;
        NewSurvivor->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        NewSurvivor->SetActorHiddenInGame(false);
        NewSurvivor->GetMesh()->SetHiddenInGame(false, true);
        NewSurvivor->GetMesh()->SetVisibility(true, true);
        NewSurvivor->GetMesh()->SetOwnerNoSee(false);
        NewSurvivor->GetMesh()->SetOnlyOwnerSee(false);
        NewSurvivor->DisableInput(nullptr);
        RemoteSurvivors.Add(PlayerId, NewSurvivor);
        UE_LOG(LogTemp, Warning, TEXT("New Remote Survivor Spawned! ID: %d"), PlayerId);
    }
}
