// Copyright Danny Kay 2021

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "SBlueprintLibrary.generated.h"

class USActionComponent;

/**
 * Game-specific blueprint library.
 * Static functions for quality of life improvements for code and in blueprints. 
 */
UCLASS()
class SHOOTERROGUELITE_API USBlueprintLibrary : public UObject
{
	GENERATED_BODY()

	UFUNCTION(BlueprintPure, Category = Game)
	USActionComponent* GetActionComponent(AActor* Actor) const;

	UFUNCTION(BlueprintPure, Category = Game)
	bool ActorHasTag(AActor* Actor, FGameplayTag Tag) const;
};
