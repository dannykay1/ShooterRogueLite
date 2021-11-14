// Copyright Danny Kay 2021

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "SInteractionWidgetComponent.generated.h"

class ASPlayerCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBeginInteract, ASPlayerCharacter*, Player);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEndInteract, ASPlayerCharacter*, Player);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBeginFocus, ASPlayerCharacter*, Player);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEndFocus, ASPlayerCharacter*, Player);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteract, ASPlayerCharacter*, Player);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SHOOTERROGUELITE_API USInteractionWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USInteractionWidgetComponent();

	/* Manually call when anything changes on the widget. */
	void RefreshWidget();

	/* Time player must hold the interact key to interact with this object. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Interaction)
	float InteractionTime;

	/* Max distance the player can be away from this actor before you can interact. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Interaction)
	float InteractionDistance;

	/* The name that will come up when the player looks at the interactable. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Interaction)
	FText InteractableNameText;

	/* Verb that describes how the interaction works, ie "Sit" for chair, "Eat" for food, etc. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Interaction)
	FText InteractableActionText;

	/* Refreshes the name of the interactable. Will refresh widget. */
	UFUNCTION(BlueprintCallable, Category = Interaction)
	void SetInteractableNameText(const FText& NewNameText);

	/* Refreshes the action text of the interactable. Will refresh widget. */
	UFUNCTION(BlueprintCallable, Category = Interaction)
	void SetInteractableActionText(const FText& NewActionText);

	UPROPERTY(EditDefaultsOnly, BlueprintAssignable)
	FOnBeginInteract OnBeginInteract;

	UPROPERTY(EditDefaultsOnly, BlueprintAssignable)
	FOnEndInteract OnEndInteract;

	UPROPERTY(EditDefaultsOnly, BlueprintAssignable)
	FOnBeginFocus OnBeginFocus;

	UPROPERTY(EditDefaultsOnly, BlueprintAssignable)
	FOnEndFocus OnEndFocus;

	UPROPERTY(EditDefaultsOnly, BlueprintAssignable)
	FOnInteract OnInteract;	

	/* Called when the player interaction check trace begins/ends hitting the item. */
	void BeginFocus(ASPlayerCharacter* Character);
	void EndFocus(ASPlayerCharacter* Character);

	/* Called when the player begins/end interaction with the item. */
	void BeginInteract(ASPlayerCharacter* Character);
	void EndInteract(ASPlayerCharacter* Character);

	/* Called when interacting with an item. */
	void Interact(ASPlayerCharacter* Character) const;

	/* Return a normalize value (0-1) denoting how far through the interact player is. */
	UFUNCTION(BlueprintPure, Category = Interaction)
	float GetInteractPercentage() const;

protected:
	/* Called when game starts. */
	virtual  void Deactivate() override;

	bool CanInteract(ASPlayerCharacter* Character) const;

	ASPlayerCharacter* Interactor;
};
