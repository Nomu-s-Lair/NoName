// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NLCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class NONAME_API UNLCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
public:
	virtual float GetMaxSpeed() const override;
	float GetVelocity() { return Velocity.Size(); };

	/** Sprint **/
	bool bIsSprinting = false;
	FORCEINLINE bool IsSprinting() { return bIsSprinting; }
	void StartSprint();
	void StopSprint();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character movement | Speed", meta = (ClampMin = 0.0f, UIMin = 0.0f))
		float SprintSpeed = 1200.0f;
};
