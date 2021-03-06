// Copyright Danny Kay 2021

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Attributes/SAttributeComponent.h"
#include "Blueprint/UserWidget.h"
#include "SAttributeWidget.generated.h"

class USAttributeComponent;

/**
 * Base widget class that listens for attribute changed.
 * i.e. used for health bar, ammo counter, etc.
 */
UCLASS()
class SHOOTERROGUELITE_API USAttributeWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Attributes)
	void InitializeWidget(USAttributeComponent* AttributeComp, FGameplayTag Tag);
	
	UPROPERTY(BlueprintReadOnly, Category = Attribute, meta = (ExposeOnSpawn = true))
	USAttributeComponent* AttributeComponent;

	UPROPERTY(BlueprintReadOnly, Category = Attribute, meta = (ExposeOnSpawn = true))
	FGameplayTag AttributeTag;
};
