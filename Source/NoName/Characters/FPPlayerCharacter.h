// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NLBaseCharacter.h"
#include "FPPlayerCharacter.generated.h"

class UCameraComponent;
class USkeletalMeshComponent;

UCLASS(Blueprintable)
class NONAME_API AFPPlayerCharacter : public ANLBaseCharacter
{
	GENERATED_BODY()



public:
	AFPPlayerCharacter(const FObjectInitializer& ObjectInitializer);

	//USkeletalMeshComponent* GetFPMesh() const { return FPMesh; }
	//UCameraComponent* GetFirstPersonCameraComponent() const { return CameraComponent; }

	virtual void MoveForward(float Value) override;
	virtual void MoveRight(float Value) override;
	virtual void TurnAtRate(float Value) override;
	virtual void Turn(float Value) override;
	virtual void LookUpAtRate(float Value) override;
	virtual void LookUp(float Value) override;

	virtual bool CanJumpInternal_Implementation() const override;
	virtual void OnJumped_Implementation() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character | Camera")
		UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character | Mesh")
		USkeletalMeshComponent* FPMesh;
	
};
