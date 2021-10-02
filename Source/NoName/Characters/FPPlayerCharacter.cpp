// Fill out your copyright notice in the Description page of Project Settings.


#include "FPPlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"

AFPPlayerCharacter::AFPPlayerCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.f);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	CameraComponent->SetupAttachment(GetCapsuleComponent());
	CameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 64.0f));
	CameraComponent->bUsePawnControlRotation = true;

	FPMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	FPMesh->SetupAttachment(CameraComponent);
	FPMesh->CastShadow = false;
	FPMesh->bCastDynamicShadow = false;
}

void AFPPlayerCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AFPPlayerCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AFPPlayerCharacter::TurnAtRate(float Value)
{
	AddControllerYawInput(Value * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AFPPlayerCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void AFPPlayerCharacter::LookUpAtRate(float Value)
{
	AddControllerPitchInput(Value * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AFPPlayerCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

bool AFPPlayerCharacter::CanJumpInternal_Implementation() const
{
	if (bIsCrouched)
	{
		ACharacter* DefaultCharacter = GetClass()->GetDefaultObject<ACharacter>();
		check(GetCapsuleComponent());
		const float CurrentCrouchedHalfHeight = GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
		const float	ComonentScale = GetCapsuleComponent()->GetShapeScale();
		const float OldUnscaledHalfHeight = GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
		const float HalfHeightAdjust = DefaultCharacter->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight() - OldUnscaledHalfHeight;
		const float ScaledHalfHeightAdjust = HalfHeightAdjust * ComonentScale;
		const FVector PawnLocation = GetCharacterMovement()->UpdatedComponent->GetComponentLocation();
		const float SweepInlation = KINDA_SMALL_NUMBER * 10.0f;

		FCollisionQueryParams CapsuleParams(SCENE_QUERY_STAT(CrouchTrace), false, this);
		FCollisionResponseParams ResponseParams;
		GetCharacterMovement()->InitCollisionParams(CapsuleParams, ResponseParams);

		float Radius, HalfHeight;
		GetCapsuleComponent()->GetScaledCapsuleSize(Radius, HalfHeight);
		FVector CapsuleExtent(Radius, Radius, HalfHeight);
		const float MinExtent = KINDA_SMALL_NUMBER * 10.0f;
		CapsuleExtent.Z = FMath::Max(CapsuleExtent.Z - (-SweepInlation - ScaledHalfHeightAdjust), MinExtent);
		const FCollisionShape StandingCapsuleShape = FCollisionShape::MakeCapsule(CapsuleExtent);
		const ECollisionChannel CollisionChannel = GetCharacterMovement()->UpdatedComponent->GetCollisionObjectType();
		FVector StandingLocation = PawnLocation + FVector(0.0f, 0.0f, StandingCapsuleShape.GetCapsuleHalfHeight() - CurrentCrouchedHalfHeight);
		bool bEncrouched = GetWorld()->OverlapBlockingTestByChannel(StandingLocation, FQuat::Identity, CollisionChannel, StandingCapsuleShape, CapsuleParams, ResponseParams);
		if (bEncrouched)
		{
			return	false;
		}
	}
	return bIsCrouched || Super::CanJumpInternal_Implementation();
}

void AFPPlayerCharacter::OnJumped_Implementation()
{
	if (bIsCrouched)
	{
		UnCrouch();
	}
}
