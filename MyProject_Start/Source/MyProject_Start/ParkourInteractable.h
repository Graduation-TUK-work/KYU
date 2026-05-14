#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyProject_Start/InteractionInterface.h"
#include "ParkourInteractable.generated.h"

UCLASS()
class MYPROJECT_START_API AParkourInteractable : public AActor, public IInteractionInterface
{
    GENERATED_BODY()

public:
    AParkourInteractable();

    virtual void StartInteract_Implementation(ACharacter* Interactor) override;
    virtual void UpdateInteract_Implementation(float DeltaTime) override;
    virtual void CancelInteract_Implementation() override;
    virtual void CompleteInteract_Implementation() override;
    virtual float GetInteractDuration_Implementation() const override;

    UFUNCTION(BlueprintCallable, Category = "Parkour")
    FVector GetVaultTargetLocation() const;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Parkour")
    class USceneComponent* SceneRoot;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Parkour")
    class UBoxComponent* InteractionVolume;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Parkour")
    class USceneComponent* VaultTargetPoint;
};
