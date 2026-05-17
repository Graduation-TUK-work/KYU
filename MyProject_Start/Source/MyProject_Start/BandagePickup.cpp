#include "MyProject_Start/BandagePickup.h"

#include "Algo/Sort.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "MyProject_Start/Player/TutorialCharacter.h"

ABandagePickup::ABandagePickup()
{
    PrimaryActorTick.bCanEverTick = false;

    SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
    SetRootComponent(SceneRoot);

    InteractionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionSphere"));
    InteractionSphere->SetupAttachment(SceneRoot);
    InteractionSphere->SetSphereRadius(50.0f);
    InteractionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    InteractionSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
    InteractionSphere->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}

void ABandagePickup::BeginPlay()
{
    Super::BeginPlay();
    AssignGeneratedIdIfNeeded();
}

void ABandagePickup::StartInteract_Implementation(ACharacter* Interactor)
{
    if (bIsCollected)
    {
        return;
    }

    ATutorialCharacter* Survivor = Cast<ATutorialCharacter>(Interactor);
    if (!Survivor || Survivor->HasBandage())
    {
        return;
    }

    Survivor->SetHasBandage(true);
    CompleteInteract_Implementation();
}

void ABandagePickup::UpdateInteract_Implementation(float DeltaTime)
{
}

void ABandagePickup::CancelInteract_Implementation()
{
}

void ABandagePickup::CompleteInteract_Implementation()
{
    ApplyCollectedState();
}

float ABandagePickup::GetInteractDuration_Implementation() const
{
    return 0.0f;
}

int32 ABandagePickup::GetBandageId() const
{
    return BandageId;
}

bool ABandagePickup::IsCollected() const
{
    return bIsCollected;
}

void ABandagePickup::ApplyCollectedState()
{
    bIsCollected = true;
    SetActorHiddenInGame(true);
    SetActorEnableCollision(false);
    SetActorTickEnabled(false);
}

void ABandagePickup::AssignGeneratedIdIfNeeded()
{
    if (BandageId >= 0 || !GetWorld())
    {
        return;
    }

    TArray<AActor*> FoundBandages;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABandagePickup::StaticClass(), FoundBandages);

    Algo::Sort(FoundBandages, [](const AActor* Left, const AActor* Right)
        {
            return Left && Right && Left->GetName() < Right->GetName();
        });

    BandageId = FoundBandages.IndexOfByKey(this);
}
