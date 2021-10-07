#include "NLBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../Components/Movement/NLCharacterMovementComponent.h"

ANLBaseCharacter::ANLBaseCharacter(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer.SetDefaultSubobjectClass<UNLCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	NLCharacterMovementComponent = StaticCast<UNLCharacterMovementComponent*>(GetCharacterMovement());
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

bool ANLBaseCharacter::CanJumpInternal_Implementation() const
{
	return Super::CanJumpInternal_Implementation();
}
