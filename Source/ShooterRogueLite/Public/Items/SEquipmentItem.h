// Copyright Danny Kay 2021

#pragma once

#include "CoreMinimal.h"
#include "SItem.h"
#include "Framework/SAssetManager.h"
#include "SEquipmentItem.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERROGUELITE_API USEquipmentItem : public USItem
{
	GENERATED_BODY()

public:
	/** Constructor, sets ItemType. */
	USEquipmentItem()
	{
		ItemType = USAssetManager::EquipmentItemType;
	}
};
