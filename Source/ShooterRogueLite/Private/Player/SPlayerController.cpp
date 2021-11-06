// Copyright Danny Kay 2021


#include "Player/SPlayerController.h"

#include "Framework/SAssetManager.h"
#include "Framework/SGameInstance.h"
#include "Items/SItem.h"


// Sets default values
ASPlayerController::ASPlayerController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ASPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AddDefaultInventory();

	NotifyInventoryLoaded();
}

void ASPlayerController::AddDefaultInventory()
{
	InventoryData.Reset();
	SlottedItems.Reset();

	// Get SGameInstance. Will be used to fill out InventoryData and SlottedItems.
	UWorld* World = GetWorld();
	USGameInstance* GameInstance = World ? World->GetGameInstance<USGameInstance>() : nullptr;

	if (!ensure(GameInstance))
	{
		UE_LOG(LogTemp, Fatal, TEXT("OnPosses: Cannot find SGameInstance! Cannot populate inventory!"));
		return;
	}

	// Fill out SlottedItems from SGameInstance's ItemSlotsPerType.
	for (const TPair<FPrimaryAssetType, int32>& Pair : GameInstance->ItemSlotsPerType)
	{
		for (int32 SlotNumber = 0; SlotNumber < Pair.Value; SlotNumber++)
		{
			SlottedItems.Add(FSItemSlot(Pair.Key, SlotNumber));
		}
	}

	USAssetManager& AssetManager = USAssetManager::Get();

	// Populate InventoryData with SGameInstance's ItemSlotsPerType.
	for (const TPair<FPrimaryAssetId, FSItemData>& Pair : GameInstance->DefaultInventory)
	{
		USItem* LoadedItem = AssetManager.ForceLoadItem(Pair.Key);
		if (LoadedItem)
		{
			InventoryData.Add(LoadedItem, Pair.Value);
		}
	}

	for (const TPair<USItem*, FSItemData>& Pair : InventoryData)
	{
		FillEmptySlotWithItem(Pair.Key);
	}
}

bool ASPlayerController::AddInventoryItem(USItem* NewItem, int32 ItemCount, bool bAutoSlot)
{
	if (!NewItem)
	{
		UE_LOG(LogTemp, Warning, TEXT("AddInventoryItem: Failed trying to add null item!"));
		return false;
	}

	if (ItemCount <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("AddInventoryItem: Failed trying to add item %s with negative count!"), *NewItem->GetName());
		return false;
	}

	// Find the current item data.
	FSItemData OldData;
	GetInventoryItemData(NewItem, OldData);

	// Find modified data.
	FSItemData NewData = OldData;
	NewData.UpdateItemData(FSItemData(ItemCount), NewItem->MaxCount);

	bool bChanged = false;

	if (OldData != NewData)
	{
		InventoryData.Add(NewItem, NewData);
		NotifyInventoryItemChanged(true, NewItem);
		bChanged = true;
	}

	if (bAutoSlot)
	{
		bChanged |= FillEmptySlotWithItem(NewItem);
	}

	return bChanged;
}

bool ASPlayerController::RemoveInventoryItem(USItem* RemovedItem, int32 RemoveCount)
{
	if (!RemovedItem)
	{
		UE_LOG(LogTemp, Warning, TEXT("RemoveInventoryItem: Failed trying to remove null item!"));
		return false;
	}

	// Find current item data.
	FSItemData NewData;
	GetInventoryItemData(RemovedItem, NewData);

	// Check if new data is valid.
	if (!NewData.IsValid())
	{
		return false;
	}

	// If removed, delete all.
	if (RemoveCount <= 0)
	{
		NewData.ItemCount = 0;
	}
	else
	{
		NewData.ItemCount -= RemoveCount;
	}

	if (NewData.ItemCount > 0)
	{
		InventoryData.Add(RemovedItem, NewData);
	}
	else
	{
		InventoryData.Remove(RemovedItem);

		for (TPair<FSItemSlot, USItem*>& Pair : SlottedItems)
		{
			if (Pair.Value && Pair.Value == RemovedItem)
			{
				Pair.Value = nullptr;
				NotifySlottedItemChanged(Pair.Key, Pair.Value);
			}
		}
	}

	NotifyInventoryItemChanged(false, RemovedItem);

	return true;
}

void ASPlayerController::GetInventoryItems(TArray<USItem*>& Items, FPrimaryAssetType ItemType)
{
	for (const TPair<USItem*, FSItemData> Pair : InventoryData)
	{
		if (Pair.Key)
		{
			FPrimaryAssetId AssetID = Pair.Key->GetPrimaryAssetId();

			if (!ItemType.IsValid() && AssetID.PrimaryAssetType == ItemType)
			{
				Items.Add(Pair.Key);
			}
		}
	}
}

int32 ASPlayerController::GetInventoryItemCount(USItem* Item) const
{
	const FSItemData* FoundItem = InventoryData.Find(Item);
	return FoundItem ? FoundItem->ItemCount : 0;
}

bool ASPlayerController::GetInventoryItemData(USItem* Item, FSItemData& ItemData) const
{
	const FSItemData* FoundItem = InventoryData.Find(Item);

	if (FoundItem)
	{
		ItemData = *FoundItem;
		return true;
	}

	ItemData = FSItemData(0);
	return false;
}

bool ASPlayerController::SetSlottedItem(FSItemSlot ItemSlot, USItem* Item)
{
	bool bFound = false;
	for (TPair<FSItemSlot, USItem*>& Pair : SlottedItems)
	{
		if (Pair.Key == ItemSlot)
		{
			bFound = true;
			Pair.Value = Item;
			NotifySlottedItemChanged(Pair.Key, Pair.Value);
		}
		else if (Item && Pair.Value == Item)
		{
			// If this item was found in another slot, remove it
			Pair.Value = nullptr;
			NotifySlottedItemChanged(Pair.Key, Pair.Value);
		}
	}

	return bFound;
}

USItem* ASPlayerController::GetSlottedItem(FSItemSlot ItemSlot) const
{
	USItem* const* FoundItem = SlottedItems.Find(ItemSlot);
	//return FoundItem ? *FoundItem : nullptr;
	return *FoundItem;
}

void ASPlayerController::GetSlottedItems(TArray<USItem*>& Items, FPrimaryAssetType ItemType, bool bOutputEmptyIndexes)
{
	for (TPair<FSItemSlot, USItem*>& Pair : SlottedItems)
	{
		if (Pair.Key.ItemType == ItemType || !ItemType.IsValid())
		{
			Items.Add(Pair.Value);
		}
	}
}

void ASPlayerController::FillEmptySlots()
{
	for (const TPair<USItem*, FSItemData>& Pair : InventoryData)
	{
		FillEmptySlotWithItem(Pair.Key);
	}
}

bool ASPlayerController::FillEmptySlotWithItem(USItem* NewItem)
{
	if (!NewItem)
	{
		UE_LOG(LogTemp, Warning, TEXT("FillEmptySlotWithItem: Trying to fill a slot with a null Item!"));
		return false;
	}

	// Look for an empty slot to place this item.
	const FPrimaryAssetType NewItemType = NewItem->GetPrimaryAssetId().PrimaryAssetType;
	FSItemSlot EmptySlot;

	for (TPair<FSItemSlot, USItem*>& Pair : SlottedItems)
	{
		if (Pair.Key.ItemType == NewItemType)
		{
			if (Pair.Value == NewItem)
			{
				// Item already in slot!
				return false;
			}
			else if (Pair.Value == nullptr && (!EmptySlot.IsValid() || EmptySlot.SlotNumber > Pair.Key.SlotNumber))
			{
				// Found empty slot.
				EmptySlot = Pair.Key;
			}
		}
	}

	if (EmptySlot.IsValid())
	{
		SlottedItems[EmptySlot] = NewItem;
		NotifySlottedItemChanged(EmptySlot, NewItem);
		return true;
	}

	return false;
}

void ASPlayerController::NotifyInventoryItemChanged(bool bAdded, USItem* Item)
{
	OnInventoryItemChanged.Broadcast(bAdded, Item);

	// Call BP update event
	InventoryItemChanged(bAdded, Item);
}

void ASPlayerController::NotifySlottedItemChanged(FSItemSlot ItemSlot, USItem* Item)
{
	OnSlottedItemChanged.Broadcast(ItemSlot, Item);

	// Call BP update event
	SlottedItemChanged(ItemSlot, Item);
}

void ASPlayerController::NotifyInventoryLoaded() const
{
	OnInventoryLoaded.Broadcast();
}
