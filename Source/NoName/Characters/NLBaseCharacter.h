// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NLBaseCharacter.generated.h"

class UNLCharacterMovementComponent;

UCLASS(Abstract, NotBlueprintable)
class NONAME_API ANLBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ANLBaseCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void Tick(float DeltaTime) override;

	virtual void MoveForward(float Value) {};
	virtual void MoveRight(float Value) {};
	virtual void TurnAtRate(float Value) {};
	virtual void Turn(float Value) {};	
	virtual void LookUpAtRate(float Value) {};
	virtual void LookUp(float Value) {};

	virtual void Jump() override;
	virtual void ChangeCrouchState();
	virtual void StartSprint();
	virtual void StopSprint();

	virtual bool CanJumpInternal_Implementation() const override;

	FORCEINLINE UNLCharacterMovementComponent* GetNLCharacterMovementComponent() { return NLCharacterMovementComponent; }
	FORCEINLINE UNLCharacterMovementComponent* GetNLCharacterMovementComponent() const { return NLCharacterMovementComponent; }

protected:
	UNLCharacterMovementComponent* NLCharacterMovementComponent = nullptr;

	bool bIsSprintRequested = false;

	virtual bool CanSprint();
	void TryChangeSprintState();
};
