// Fill out your copyright notice in the Description page of Project Settings.


#include "NLCharacterMovementComponent.h"

float UNLCharacterMovementComponent::GetMaxSpeed() const
{
	float Result = Super::GetMaxSpeed();

	if(bIsSprinting)
	{
		Result = SprintSpeed;
	}

	return Result;
}

void UNLCharacterMovementComponent::StartSprint()
{
	bIsSprinting = true;
	bForceMaxAccel = 1;
}

void UNLCharacterMovementComponent::StopSprint()
{
	bIsSprinting = false;
	bForceMaxAccel = 0;
}
