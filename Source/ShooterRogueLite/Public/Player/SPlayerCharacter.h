// Copyright Danny Kay 2021

#pragma once

#include "CoreMinimal.h"
#include "Characters/SCharacter.h"
#include "SPlayerCharacter.generated.h"

class UCameraComponent;
class USkeletalMeshComponent;
class USInteractionComponent;

UCLASS()
class SHOOTERROGUELITE_API ASPlayerCharacter : public ASCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASPlayerCharacter();

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Components)
	UCameraComponent* CameraComponent;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Components)
	USkeletalMeshComponent* Mesh1P;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Components)
	USInteractionComponent* InteractionComponent;

	void MoveForward(float Value);
	void MoveRight(float Value);

public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintPure)
	FORCEINLINE UCameraComponent* GetCameraComponent() const { return CameraComponent; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }

	UFUNCTION(BlueprintPure, BlueprintImplementableEvent, Category = Animation)
	FTransform GetAimDownSightTransform() const;

	UFUNCTION(BlueprintPure, BlueprintImplementableEvent, Category = Animation)
	FTransform GetRightHandSocketTransform() const;

	UFUNCTION(BlueprintPure, BlueprintImplementableEvent, Category = Animation)
	FTransform GetLeftHandTransform() const;
};
