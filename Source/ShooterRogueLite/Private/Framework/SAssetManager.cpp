// Copyright Danny Kay 2021

#include "Framework/SAssetManager.h"
#include "Items/SItem.h"

const FPrimaryAssetType	USAssetManager::WeaponItemType = TEXT("Weapon");
const FPrimaryAssetType	USAssetManager::EquipmentItemType = TEXT("Equipment");
const FPrimaryAssetType	USAssetManager::PotionItemType = TEXT("Potion");

USAssetManager& USAssetManager::Get()
{
	USAssetManager* This = Cast<USAssetManager>(GEngine->AssetManager);

	if (This)
	{
		return *This;
	}

	UE_LOG(LogTemp, Fatal, TEXT("Invalid AssetManager in DefaultEngine.ini, must be SAssetManager"));
	return *NewObject<USAssetManager>(); // never call this, must return a value to compile.
}

void USAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	// Perform any initialization here.
}

USItem* USAssetManager::ForceLoadItem(const FPrimaryAssetId& PrimaryAssetId, const bool bLogWarning)
{
	const FSoftObjectPath ItemPath = GetPrimaryAssetPath(PrimaryAssetId);

	// Loads asynchronously, may hitch!
	USItem* LoadedItem = Cast<USItem>(ItemPath.TryLoad());

	if (bLogWarning && !LoadedItem)
	{
		UE_LOG(LogTemp, Warning, TEXT("ForceLoadItem: Failed to load item for identifier %s!"), *PrimaryAssetId.ToString());
	}

	return LoadedItem;
}
