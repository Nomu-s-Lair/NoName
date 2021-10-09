// Fill out your copyright notice in the Description page of Project Settings.


#include "../Animations/NLAnimInstance.h"
#include "../NLBaseCharacter.h"
#include "../../Components/Movement/NLCharacterMovementComponent.h"

void UNLAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	checkf(TryGetPawnOwner()->IsA<ANLBaseCharacter>(), TEXT("UNLCharacterAnimInstance::NativeBeginPlay() UNLCharacterAnimInstance can be used only with ANLBaseCharacter"));
	CachedBaseCharacter = StaticCast<ANLBaseCharacter*>(TryGetPawnOwner());
}

void UNLAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!CachedBaseCharacter.IsValid())
	{
		return;
	}

	UNLCharacterMovementComponent* CharacterMovement = CachedBaseCharacter->GetNLCharacterMovementComponent();

	Speed = CharacterMovement->GetVelocity();
	bIsFalling = CharacterMovement->IsFalling();
	bIsCrouching = CharacterMovement->IsCrouching();
	bIsSprinting = CharacterMovement->IsSprinting();
}
