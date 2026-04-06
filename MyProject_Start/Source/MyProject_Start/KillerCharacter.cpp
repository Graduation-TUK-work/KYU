// Fill out your copyright notice in the Description page of Project Settings.


#include "KillerCharacter.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AKillerCharacter::AKillerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FPSCamerComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirePersonCamera"));
	FPSCamerComponent->SetupAttachment(GetCapsuleComponent());
	FPSCamerComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
	FPSCamerComponent->bUsePawnControlRotation = true;

	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	FPSMesh->SetOnlyOwnerSee(true);
	FPSMesh->SetupAttachment(FPSCamerComponent);

	FPSMesh->bCastDynamicShadow = false;
	FPSMesh->CastShadow = false;

	GetMesh()->SetOwnerNoSee(true);

}

// Called when the game starts or when spawned
void AKillerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("KillerCharacter"));
	}
	
}

// Called every frame
void AKillerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AKillerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	InputComponent->BindAxis("MoveForward", this, &AKillerCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AKillerCharacter::MoveRight);


	InputComponent->BindAxis("TurnCamera", this, &AKillerCharacter::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &AKillerCharacter::AddControllerPitchInput);
}

void AKillerCharacter::MoveForward(float AxisValue)
{


	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, AxisValue);
}


void AKillerCharacter::MoveRight(float AxisValue)
{


	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, AxisValue);
}

