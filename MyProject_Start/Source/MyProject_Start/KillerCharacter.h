// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "KillerCharacter.generated.h"

class FNetworkWorker;
class ATutorialCharacter;

UCLASS()
class MYPROJECT_START_API AKillerCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AKillerCharacter();

    static TMap<int32, AKillerCharacter*> RemoteKillers;
    static TMap<int32, ATutorialCharacter*> RemoteSurvivors;

protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void CheckHit();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    float AttackRange = 200.00f;

    bool bHasDealtDamage = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Carry")
    ATutorialCharacter* CarriedSurvivor;

    void PickupSurvivor();
    void DropSurvivor();

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
    class UAnimMontage* PickupMontage;

    UPROPERTY(BlueprintReadOnly, Category = "Movement")
    float MovementSpeed;

    UPROPERTY(BlueprintReadOnly, Category = "NetworkData")
    float RemoteMovementSpeed = 0.0f;

public:
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    float GetMovementSpeed() const { return MovementSpeed; }
    float GetRemoteMovementSpeed() const { return RemoteMovementSpeed; }
    float GetRemoteForwardValue() const { return RemoteForwardValue; }
    float GetRemoteRightValue() const { return RemoteRightValue; }
    bool GetRemoteIsAttacking() const { return RemoteIsAttacking; }
    void SetRemoteForwardValue(float Value) { RemoteForwardValue = Value; }
    void SetRemoteRightValue(float Value) { RemoteRightValue = Value; }
    void SetRemoteMovementSpeed(float Value) { RemoteMovementSpeed = Value; }
    void SetRemoteIsAttacking(bool bValue) { RemoteIsAttacking = bValue; }

    UFUNCTION()
    void MoveForward(float AxisValue);

    UFUNCTION()
    void MoveRight(float AxisValue);

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void StartAttack();

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void EndAttack();

    void SendLocationToServer();
    void UpdateRemoteKiller(int32 PlayerId, FVector Location, float RotationYaw, float Forward, float Right, bool bSprint);
    void UpdateRemoteSurvivor(int32 PlayerId, FVector Location, float RotationYaw, float Forward, float Right, bool bSprint);

    UPROPERTY()
    float MoveForwardValue = 0;

    UPROPERTY()
    float MoveRightValue = 0;

    UPROPERTY(BlueprintReadOnly, Category = "NetworkData")
    float RemoteForwardValue = 0.0f;

    UPROPERTY(BlueprintReadOnly, Category = "NetworkData")
    float RemoteRightValue = 0.0f;

    UPROPERTY(BlueprintReadOnly, Category = "NetworkData")
    bool RemoteIsAttacking = false;

    FNetworkWorker* NetworkWorker;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Network")
    int32 MyPlayerId = -1;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Status")
    bool bIsAttacking;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
    class UAnimMontage* AttackMontage;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    UCameraComponent* FPSCamerComponent;

    UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
    USkeletalMeshComponent* FPSMesh;

    UPROPERTY(EditAnywhere, Category = "Multiplayer|Classes")
    TSubclassOf<AKillerCharacter> KillerBPClass;

    UPROPERTY(EditAnywhere, Category = "Multiplayer|Classes")
    TSubclassOf<ATutorialCharacter> SurvivorBPClass;
};
