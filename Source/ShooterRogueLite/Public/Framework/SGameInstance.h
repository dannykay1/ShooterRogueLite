// Copyright Danny Kay 2021

#pragma once

#include "CoreMinimal.h"
#include "STypes.h"
#include "Engine/GameInstance.h"
#include "SGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERROGUELITE_API USGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	// Constructor
	USGameInstance();

	/** List of inventory items to add to new players */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inventory)
	TMap<FPrimaryAssetId, FSItemData> DefaultInventory;

	/** Number of slots for each type of item that player uses. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inventory)
	TMap<FPrimaryAssetType, int32> ItemSlotsPerType;
};
