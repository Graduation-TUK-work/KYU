#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyProject_Start/InteractionInterface.h"
#include "BandagePickup.generated.h"

UCLASS()
class MYPROJECT_START_API ABandagePickup : public AActor, public IInteractionInterface
{
    GENERATED_BODY()

public:
    ABandagePickup();

    virtual void StartInteract_Implementation(ACharacter* Interactor) override;
    virtual void UpdateInteract_Implementation(float DeltaTime) override;
    virtual void CancelInteract_Implementation() override;
    virtual void CompleteInteract_Implementation() override;
    virtual float GetInteractDuration_Implementation() const override;

    UFUNCTION(BlueprintCallable, Category = "Bandage")
    int32 GetBandageId() const;

    UFUNCTION(BlueprintCallable, Category = "Bandage")
    bool IsCollected() const;

    void ApplyCollectedState();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bandage")
    class USceneComponent* SceneRoot;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bandage")
    class USphereComponent* InteractionSphere;

private:
    void AssignGeneratedIdIfNeeded();

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bandage", meta = (AllowPrivateAccess = "true"))
    int32 BandageId = -1;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bandage", meta = (AllowPrivateAccess = "true"))
    bool bIsCollected = false;
};
