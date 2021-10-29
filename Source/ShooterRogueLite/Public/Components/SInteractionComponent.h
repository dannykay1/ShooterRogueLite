// Copyright Danny Kay 2021

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SInteractionComponent.generated.h"

class ASCharacter;
class USInteractionWidgetComponent;

/*
 * Component that handles any player interaction with any
 * actor that implements the SInteractionInterace
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SHOOTERROGUELITE_API USInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USInteractionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/* Current interactable widget component this component is viewing, if any. */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Interaction)
	USInteractionWidgetComponent* ViewedInteractionComponent;

	/* Character that owns this interaction component. */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Interaction)
	ASCharacter* CharacterOwner;

	/* Time when this component last checked for an interactable widget component. */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Interaction)
	float LastInteractionCheckTime;

	/* Whether interact input is held down. */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Interaction)
	bool bInteractHeld;

	/* How often in seconds to check for interactable widget component. */
	UPROPERTY(EditDefaultsOnly, Category = Interaction)
	float InteractionCheckFrequency;

	/* How far to check for any interactable. */
	UPROPERTY(EditDefaultsOnly, Category = Interaction)
	float InteractionCheckDistance;

	/* How thick sphere trace will be to detect any interactable. */
	UPROPERTY(EditDefaultsOnly, Category = Interaction)
	float InteractionCheckRadius;

	/* Finds an interactable the owner is looking at. */
	void PerformInteractionCheck();

	void CouldntFindInteractable();
	void FoundNewInteractable(USInteractionWidgetComponent* Interactable);

	/* Helper function to return the viewed interactable, if any. */
	FORCEINLINE USInteractionWidgetComponent* GetInteractable() const { return ViewedInteractionComponent; }

	FTimerHandle TimerHandle_Interact;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Interact();

	void BeginInteract();
    void EndInteract();

	/* True if interacting with an item that has an interaction time. */
	bool IsInteracting() const;
	
	/* Get the time remaining until interaction is complete. */
	float GetRemainingInteractionTime() const;
};
