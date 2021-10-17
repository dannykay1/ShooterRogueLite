// Copyright Danny Kay 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class UCameraComponent;
class USkeletalMeshComponent;
class USInteractionComponent;

UCLASS()
class SHOOTERROGUELITE_API ASCharacter : public ACharacter
{
	GENERATED_BODY()
	
public:
	// Sets default values for this character's properties
	ASCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Components)
	UCameraComponent* CameraComponent;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Components)
	USkeletalMeshComponent* Mesh1P;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Components)
	USInteractionComponent* InteractionComponent;
	
	void MoveForward(float Value);
	void MoveRight(float Value);

	void BeginInteract();
	void EndInteract();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION(BlueprintPure)
	FORCEINLINE UCameraComponent* GetCameraComponent() const { return CameraComponent; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
};