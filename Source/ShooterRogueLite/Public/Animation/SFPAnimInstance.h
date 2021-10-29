﻿// Copyright Danny Kay 2021

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimInstance.h"
#include "SFPAnimInstance.generated.h"

class ASCharacter;

/**
 * Anim instance class to handle any first person animations.
 */
UCLASS()
class SHOOTERROGUELITE_API USFPAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	/* Sets all default values. */
	USFPAnimInstance();

	/* Performs initialization. */
	virtual void NativeInitializeAnimation() override;

	/* Updates the animation. */
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = Animation)
	void InitializeTransforms();

	UFUNCTION(BlueprintCallable, Category = Animation)
	void SetRecoil(FTransform NewRecoil);

protected:
	/* The owner of the animation. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Animation)
	ASCharacter* CharacterOwner;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = Animation)
	FTransform GetSightTransform();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = Animation)
	FTransform GetRelativeHandTransform();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = Animation)
	FTransform GetLeftHandIKTransform();

	void InitializeTransforms_Delayed();
	void CalculateRotators(float DeltaSeconds);
	void CalculateRecoil(float DeltaSeconds);

	/* Is character moving? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	uint8 bIsMoving : 1;

	/* Is character sprinting? True if ActionComponent has SprintingTag. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	uint8 bIsSprinting : 1;

	/* Tag on the Action component to determine if character is sprinting. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	FGameplayTag SprintingTag;

	/* Is character falling?*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	uint8 bIsFalling : 1;

	/* Is character dead?  Based on HealthComponent. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	uint8 bIsDead : 1;

	/* Is character crouching?*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	uint8 bIsCrouching : 1;

	/* Pitch of character.  Used for aim offsets. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	float Pitch;

	/* Speed of the character. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	FTransform SightTransform;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	FTransform RelativeHandTransform;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	FTransform LeftHandIKTransform;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	FTransform RecoilTransform;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	FTransform FinalRecoilTransform;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	FRotator SwayRotation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	FRotator OldRotation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	FRotator UnmodifiedRotation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	float AimDelta;
};
