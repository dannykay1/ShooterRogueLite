// Copyright Danny Kay 2021

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "SAttributeComponent.h"
#include "Engine/DataAsset.h"
#include "SStartingAttributesData.generated.h"

/**
 * Quality of life asset. Actors with AttributeComponent will have starting attributes from
 * these assets.
 */
UCLASS()
class SHOOTERROGUELITE_API USStartingAttributesData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Attributes)
	TMap<FGameplayTag, FAttribute> Attributes;
};
