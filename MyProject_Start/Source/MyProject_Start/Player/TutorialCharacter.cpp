// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject_Start/Player/TutorialCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ATutorialCharacter::ATutorialCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	bCanVault = false;

	PrimaryActorTick.bCanEverTick = true;
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

	GetMesh()->SetRelativeLocationAndRotation(
		FVector(0.f, 0.f, -88.f),
		FRotator(0.f, -90.f, 0.f)
	);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("/Script/Engine.SkeletalMesh'/Game/Animation/Walking.Walking''"));

	if (SM.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM.Object);
	}
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 250.f, 0.f);

}

// Called when the game starts or when spawned
void ATutorialCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATutorialCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsVaultMoving)
	{
		VaultAlpha += DeltaTime * 2.0f; // 속도 조절


		if (VaultAlpha >= 1.0f)
		{
			bIsVaultMoving = false;
			bIsVaulting = false;
		}
	}

	// 카메라와 캐릭터 방향 차이 계산
	if (Controller)
	{
		FRotator ControlRot = Controller->GetControlRotation();
		FRotator ActorRot = GetActorRotation();

		FRotator Delta = UKismetMathLibrary::NormalizedDeltaRotator(ControlRot, ActorRot);

		AimYaw = Delta.Yaw;
		AimPitch = Delta.Pitch;
	}

}

// Called to bind functionality to input
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
	// PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ATutorialCharacter::Vault);
	PlayerInputComponent->BindAction("Vault", IE_Pressed, this, &ATutorialCharacter::TryVault);

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

void ATutorialCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void ATutorialCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

// 달리기, 앉기
void ATutorialCharacter::BeginCrouch()
{
	Crouch();
}

void ATutorialCharacter::EndCrouch()
{
	UnCrouch();
}
void ATutorialCharacter::BeginSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 1000.0f;
}

void ATutorialCharacter::EndSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
}

//void ATutorialCharacter::Vault()
//{
//	// 창틀 근처이고, 현재 점프 중이 아닐 때만 실행
//	if (bCanVault && VaultMontage && !GetCharacterMovement()->IsFalling())
//	{
//		// 1. 애니메이션 몽타주 재생
//		PlayAnimMontage(VaultMontage);
//
//		// 2. 캐릭터가 넘는 동안은 이동을 멈추거나 방해받지 않게 설정 (선택)
//		// GetCharacterMovement()->SetMovementMode(MOVE_None); 
//
//		UE_LOG(LogTemp, Warning, TEXT("Vaulting Start!"));
//	}
//	else
//	{
//		// 창틀 근처가 아니면 평소처럼 점프
//		Jump();
//	}
//}

void ATutorialCharacter::TryVault()
{
	if (bIsVaulting) return;

	FVector Start = GetActorLocation() + FVector(0, 0, 10);
	FVector End = Start + GetActorForwardVector() * 150;

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		Hit,
		Start,
		End,
		ECC_Visibility,
		Params
	);


	// 디버그 라인
	DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 2.0f);

	if (bHit)
	{
		// 위 공간 체크
		FVector TopStart = Hit.ImpactPoint + FVector(0, 0, 100);
		FVector TopEnd = TopStart + FVector(0, 0, 50);
		FHitResult TopHit;
		FVector Forward = GetActorForwardVector();
		FVector TargetLocation = Hit.ImpactPoint + Forward * 100;
		TargetLocation.Z += 50;

		bool bTopBlocked = GetWorld()->LineTraceSingleByChannel(
			TopHit,
			TopStart,
			TopEnd,
			ECC_Visibility,
			Params
		);

		if (!bTopBlocked)
		{
			bIsVaulting = true;

			// 👉 목표 위치 (이미 너 계산해둔 TargetLocation)
			FVector WarpTarget = TargetLocation;

			// 👉 Motion Warping에 목표 전달
			MotionWarping->AddOrUpdateWarpTargetFromLocation(
				FName("VaultTarget"),
				WarpTarget
			);

			// 👉 애니메이션 실행
			if (VaultMontage)
			{
				PlayAnimMontage(VaultMontage);
			}
		}
	}
}
