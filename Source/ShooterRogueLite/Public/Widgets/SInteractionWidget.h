// Copyright Danny Kay 2021

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SInteractionWidget.generated.h"

class USInteractionWidgetComponent;

/**
 * Base widget for any actor that is interactable.
 */
UCLASS()
class SHOOTERROGUELITE_API USInteractionWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = Interaction)
	void UpdateInteractionWidget(USInteractionWidgetComponent* InteractionComponent);

	UFUNCTION(BlueprintImplementableEvent)
	void OnUpdateInteractionWidget();

	UPROPERTY(BlueprintReadOnly, Category = Interaction, meta = (ExposeOnSpawn))
	USInteractionWidgetComponent* OwningInteractionComponent;
};
