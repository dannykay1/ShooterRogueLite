// Copyright Danny Kay 2021

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "SAssetManager.generated.h"

class USItem;

/**
 * Responsible for loading assets, primarily SItem's
 */
UCLASS()
class SHOOTERROGUELITE_API USAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	virtual void StartInitialLoading() override;

	/** Static types for SItem types. */
	static const FPrimaryAssetType WeaponItemType;
	static const FPrimaryAssetType EquipmentItemType;
	static const FPrimaryAssetType PotionItemType;

	/** Returns the current AssetManager object */
	static USAssetManager& Get();

	/**
	 * @brief Synchronously loads an SItem subclass.
	 * 
	 * @param PrimaryAssetId The asset identifier to load
	 * @param LogWarning If true, will log a warning if the item failed to load
	 * @return Returns the SItem with the PrimaryAssetId
	 */
	USItem* ForceLoadItem(const FPrimaryAssetId& PrimaryAssetId, const bool bLogWarning = true);
};
