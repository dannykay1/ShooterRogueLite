// Copyright Danny Kay 2021

#pragma once

#include "CoreMinimal.h"
#include "SItem.h"
#include "Framework/SAssetManager.h"
#include "SWeaponItem.generated.h"

class ASWeapon;

/**
 * 
 */
UCLASS()
class SHOOTERROGUELITE_API USWeaponItem : public USItem
{
	GENERATED_BODY()

public:
	/** Constructor, sets ItemType. */
	USWeaponItem()
	{
		ItemType = USAssetManager::WeaponItemType;
	}

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon)
	TSubclassOf<ASWeapon> WeaponClass;
};
