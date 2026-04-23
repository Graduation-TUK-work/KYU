// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "KillerCharacter.generated.h"

UCLASS()
class MYPROJECT_START_API AKillerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AKillerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// 실제 데미지 판정을 수행할 함수
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void CheckHit();

	// 공격 사거리
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float AttackRange = 200.00f;

	bool bHasDealtDamage = false;

	// 현재 들고 있는 생존자
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Carry")
	class ATutorialCharacter* CarriedSurvivor;

	// 생존자 들기 함수
	void PickupSurvivor();

	// 생존자 내려놓기 함수 (나중에 갈고리에 걸거나 바닥에 둘 때 사용)
	void DropSurvivor();

	// 생존자를 들어 올릴 때 재생할 몽타주
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	class UAnimMontage* PickupMontage;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float MovementSpeed;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// --- 이동 관련 함수 ---
	UFUNCTION()
	void MoveForward(float AxisValue);

	UFUNCTION()
	void MoveRight(float AxisValue);

	// --- 공격 관련 로직 (추가됨) ---
	UFUNCTION(BlueprintCallable, Category = "Combat") // <- BlueprintCallable 추가!
		void StartAttack();

	UFUNCTION(BlueprintCallable, Category = "Combat") // <- BlueprintCallable 추가!
		void EndAttack();

	// 현재 공격 중인지 여부 (애니메이션 블루프린트에서 참조 가능)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Status")
	bool bIsAttacking;

	// 에디터에서 할당할 공격 몽타주
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	class UAnimMontage* AttackMontage;

	// --- 컴포넌트 ---
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* FPSCamerComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	USkeletalMeshComponent* FPSMesh;
};