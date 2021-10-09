// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NLPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class NONAME_API ANLPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void SetPawn(APawn* InPawn) override;

protected:
	virtual void SetupInputComponent() override;

private:
	//Inut Axis
	void MoveForward(float Value);
	void MoveRight(float Value);
	void TurnAtRate(float Value);
	void Turn(float Value);
	void LookUpAtRate(float Value);
	void LookUp(float Value);

	//Input Actions
	void Jump();
	void ChangeCrouchState();
	void StartSprint();
	void StopSprint();

	TSoftObjectPtr<class ANLBaseCharacter> CachedBaseCharacter;
	
};
