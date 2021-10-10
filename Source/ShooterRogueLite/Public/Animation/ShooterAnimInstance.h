// Copyright Danny Kay 2021

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ShooterAnimInstance.generated.h"

class ACharacter;

/**
 * Base class for all characters with animations.
 */
UCLASS()
class SHOOTERROGUELITE_API UShooterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	/* Sets all default values. */
	UShooterAnimInstance();

	/* Performs initialization. */
	virtual void NativeInitializeAnimation() override;

	/* Updates the animation. */
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	/* The owner of the animation. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
	ACharacter* CharacterOwner;

	/* Is character moving? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	uint8 bIsMoving : 1;

	/* Is character sprinting? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	uint8 bIsSprinting : 1;

	/* Is character zooming weapon? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	uint8 bIsTargeting : 1;

	/* Is character falling?*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	uint8 bIsFalling : 1;

	/* Is character dead?  Based on HealthComponent. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	uint8 bIsDead : 1;

	/* Is character crouching?*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	uint8 bIsCrouching : 1;

	/* Pitch of character.  Used for aim offsets. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	float Pitch;

	/* Direction based on character velocity and rotation. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	float Direction;

	/* Speed of the character. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	float Speed;
};
