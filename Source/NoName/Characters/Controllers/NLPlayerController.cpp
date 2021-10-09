// Fill out your copyright notice in the Description page of Project Settings.


#include "NLPlayerController.h"
#include "../NLBaseCharacter.h"

void ANLPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	CachedBaseCharacter = Cast<ANLBaseCharacter>(InPawn);
}

void ANLPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &ANLPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ANLPlayerController::MoveRight);
	InputComponent->BindAxis("TurnAtRate", this, &ANLPlayerController::TurnAtRate);
	InputComponent->BindAxis("Turn", this, &ANLPlayerController::Turn);
	InputComponent->BindAxis("LookUpAtRate", this, &ANLPlayerController::LookUpAtRate);
	InputComponent->BindAxis("LookUp", this, &ANLPlayerController::LookUp);

	InputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ANLPlayerController::Jump);
	InputComponent->BindAction("Crouch", EInputEvent::IE_Pressed, this, &ANLPlayerController::ChangeCrouchState);
	InputComponent->BindAction("Sprint", EInputEvent::IE_Pressed, this, &ANLPlayerController::StartSprint);
	InputComponent->BindAction("Sprint", EInputEvent::IE_Released, this, &ANLPlayerController::StopSprint);
}

void ANLPlayerController::MoveForward(float Value)
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->MoveForward(Value);
	}
}

void ANLPlayerController::MoveRight(float Value)
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->MoveRight(Value);
	}
}

void ANLPlayerController::TurnAtRate(float Value)
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->TurnAtRate(Value);
	}
}

void ANLPlayerController::Turn(float Value)
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->Turn(Value);
	}
}

void ANLPlayerController::LookUpAtRate(float Value)
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->LookUpAtRate(Value);
	}
}

void ANLPlayerController::LookUp(float Value)
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->LookUp(Value);
	}
}

void ANLPlayerController::Jump()
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->Jump();
	}
}

void ANLPlayerController::ChangeCrouchState()
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->ChangeCrouchState();
	}
}

void ANLPlayerController::StartSprint()
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->StartSprint();
	}
}

void ANLPlayerController::StopSprint()
{
	if (CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->StopSprint();
	}
}
