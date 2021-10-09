#include "NLBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../Components/Movement/NLCharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

ANLBaseCharacter::ANLBaseCharacter(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer.SetDefaultSubobjectClass<UNLCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	NLCharacterMovementComponent = StaticCast<UNLCharacterMovementComponent*>(GetCharacterMovement());
}

void ANLBaseCharacter::Tick(float DeltaTime)
{
	TryChangeSprintState();
}

void ANLBaseCharacter::Jump()
{
	if (bIsCrouched)
	{
		GetCharacterMovement()->bWantsToCrouch = false;
	}
	else
	{
		Super::Jump();
	}
}

void ANLBaseCharacter::ChangeCrouchState()
{
	if (!GetCharacterMovement()->IsCrouching())
	{
		Crouch();
	}
	else
	{
		UnCrouch();
	}
}

void ANLBaseCharacter::StartSprint()
{
	bIsSprintRequested = true;
	
	if (bIsCrouched)
	{
		UnCrouch();
	}
}

void ANLBaseCharacter::StopSprint()
{
	bIsSprintRequested = false;
}

bool ANLBaseCharacter::CanJumpInternal_Implementation() const
{
	return Super::CanJumpInternal_Implementation();
}

bool ANLBaseCharacter::CanSprint()
{
	if (bIsCrouched)
	{
		FHitResult OutHint;
		FVector StartPosition = GetCharacterMovement()->UpdatedComponent->GetComponentLocation();
		FVector UpVector = GetCapsuleComponent()->GetUpVector();
		FVector EndPosition = ((UpVector * GetCapsuleComponent()->GetScaledCapsuleHalfHeight() + 10.0f) + StartPosition);
		FCollisionQueryParams  CollisionParams;

		if (GetWorld()->LineTraceSingleByChannel(OutHint, StartPosition, EndPosition, ECC_Visibility, CollisionParams))
		{
			if (OutHint.bBlockingHit)
			{
				return false;
			}
		}

		return  false;
	}

	if (NLCharacterMovementComponent->GetLastUpdateVelocity().IsZero())
	{
		return false;
	}

	if (GetNLCharacterMovementComponent()->IsFalling())
	{
		return false;
	}

	return true;
}

void ANLBaseCharacter::TryChangeSprintState()
{
	if (bIsSprintRequested && !GetNLCharacterMovementComponent()->IsSprinting() && CanSprint())
	{
		GetNLCharacterMovementComponent()->StartSprint();
	}

	if (!bIsSprintRequested && GetNLCharacterMovementComponent()->IsSprinting())
	{
		GetNLCharacterMovementComponent()->StopSprint();
	}
}
