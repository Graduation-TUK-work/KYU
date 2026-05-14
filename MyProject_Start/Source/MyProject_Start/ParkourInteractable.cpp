#include "MyProject_Start/ParkourInteractable.h"

#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"

AParkourInteractable::AParkourInteractable()
{
    PrimaryActorTick.bCanEverTick = false;

    SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
    SetRootComponent(SceneRoot);

    InteractionVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionVolume"));
    InteractionVolume->SetupAttachment(SceneRoot);
    InteractionVolume->SetBoxExtent(FVector(60.0f, 120.0f, 80.0f));
    InteractionVolume->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    InteractionVolume->SetCollisionResponseToAllChannels(ECR_Ignore);
    InteractionVolume->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

    VaultTargetPoint = CreateDefaultSubobject<USceneComponent>(TEXT("VaultTargetPoint"));
    VaultTargetPoint->SetupAttachment(SceneRoot);
    VaultTargetPoint->SetRelativeLocation(FVector(120.0f, 0.0f, 50.0f));
}

void AParkourInteractable::StartInteract_Implementation(ACharacter* Interactor)
{
}

void AParkourInteractable::UpdateInteract_Implementation(float DeltaTime)
{
}

void AParkourInteractable::CancelInteract_Implementation()
{
}

void AParkourInteractable::CompleteInteract_Implementation()
{
}

float AParkourInteractable::GetInteractDuration_Implementation() const
{
    return 0.0f;
}

FVector AParkourInteractable::GetVaultTargetLocation() const
{
    return VaultTargetPoint ? VaultTargetPoint->GetComponentLocation() : GetActorLocation();
}
