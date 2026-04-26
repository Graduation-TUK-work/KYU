// Fill out your copyright notice in the Description page of Project Settings.

#include "KillerAnimInstance.h"
#include "GameFramework/Pawn.h"
#include "MyProject_Start/KillerCharacter.h"

namespace
{
    float CalculateDirectionFromVelocity(const FVector& Velocity, const FRotator& ActorRotation)
    {
        FVector HorizontalVelocity = Velocity;
        HorizontalVelocity.Z = 0.0f;

        if (HorizontalVelocity.IsNearlyZero())
        {
            return 0.0f;
        }

        const FVector LocalVelocity = ActorRotation.UnrotateVector(HorizontalVelocity.GetSafeNormal());
        return FMath::RadiansToDegrees(FMath::Atan2(LocalVelocity.Y, LocalVelocity.X));
    }
}

void UKillerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    APawn* Pawn = TryGetPawnOwner();
    if (!IsValid(Pawn))
    {
        return;
    }

    AKillerCharacter* Character = Cast<AKillerCharacter>(Pawn);
    if (!Character)
    {
        return;
    }

    if (Character->IsPlayerControlled())
    {
        Speed = Character->GetMovementSpeed();
        Direction = CalculateDirectionFromVelocity(Character->GetVelocity(), Character->GetActorRotation());
        bIsAttacking = Character->bIsAttacking;
    }
    else
    {
        Speed = Character->GetRemoteMovementSpeed();
        Direction = FMath::RadiansToDegrees(FMath::Atan2(Character->GetRemoteRightValue(), Character->GetRemoteForwardValue()));
        bIsAttacking = Character->GetRemoteIsAttacking();
    }
}
