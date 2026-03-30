// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MotionWarpingComponent.h"
#include "TutorialCharacter.generated.h"

UCLASS()
class MYPROJECT_START_API ATutorialCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATutorialCharacter();
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);

	// 달리기, 앉기
	void BeginSprint();
	void EndSprint();
	void BeginCrouch();
	void EndCrouch();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// 블루프린트에서 호출할 함수(파쿠르)
	UFUNCTION(BlueprintCallable)
	void SetCanVault(bool CanIt) { bCanVault = CanIt; }

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UPROPERTY()
	float MoveForwardValue = 0;
	UPROPERTY()
	float MoveRightValue = 0;
	// 카메라 머리 방향 회전 변수
	UPROPERTY(BlueprintReadOnly)
	float AimYaw = 0;
	UPROPERTY(BlueprintReadOnly)
	float AimPitch = 0;
protected:
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;
	// 파쿠르 관련 변수, 함수
	bool bCanVault;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vault")
	UAnimMontage* VaultMontage;

	UPROPERTY(VisibleAnywhere)
	UMotionWarpingComponent* MotionWarping;

	// 파쿠르
	void TryVault();
	bool bIsVaulting = false;
	FVector VaultStartLocation;
	FVector VaultTargetLocation;

	bool bIsVaultMoving = false;
	float VaultAlpha = 0.0f;
};
