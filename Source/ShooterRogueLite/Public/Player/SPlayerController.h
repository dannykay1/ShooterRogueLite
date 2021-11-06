// Copyright Danny Kay 2021

#pragma once

#include "CoreMinimal.h"
#include "STypes.h"
#include "GameFramework/PlayerController.h"
#include "SPlayerController.generated.h"

class USItem;

/* Base class for PlayerController. */
UCLASS()
class SHOOTERROGUELITE_API ASPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASPlayerController();

	/** Map of all items owned by this player. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory)
	TMap<USItem*, FSItemData> InventoryData;

	/** Map of slots, initialized from SGameInstance. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory)
	TMap<FSItemSlot, USItem*> SlottedItems;

	/** Delegate called when an inventory item has been added or removed. */
	UPROPERTY(BlueprintAssignable, Category = Inventory)
	FOnInventoryItemChanged OnInventoryItemChanged;

	/** Delegate called when an inventory slot has been changed. */
	UPROPERTY(BlueprintAssignable, Category = Inventory)
	FOnSlottedItemChanged OnSlottedItemChanged;

	/** Called after the inventory was changed and all delegates notified. */
	UFUNCTION(BlueprintImplementableEvent, Category = Inventory)
	void InventoryItemChanged(bool bAdded, USItem* Item);

	/** Called after an item was equipped and all delegates notified. */
	UFUNCTION(BlueprintImplementableEvent, Category = Inventory)
	void SlottedItemChanged(FSItemSlot ItemSlot, USItem* Item);

	/** Delegate called when the inventory has been loaded/reloaded */
	UPROPERTY(BlueprintAssignable, Category = Inventory)
	FOnInventoryLoaded OnInventoryLoaded;

	/** Adds a new inventory item, will add it to an empty slot if possible. If the item supports count you can add more than one count. It will also update the level when adding if required */
	UFUNCTION(BlueprintCallable, Category = Inventory)
	bool AddInventoryItem(USItem* NewItem, int32 ItemCount = 1, bool bAutoSlot = true);

	/** Remove an inventory item, will also remove from slots. A remove count of <= 0 means to remove all copies */
	UFUNCTION(BlueprintCallable, Category = Inventory)
	bool RemoveInventoryItem(USItem* RemovedItem, int32 RemoveCount = 1);

	/** Returns all inventory items of a given type. If none is passed as type it will return all */
	UFUNCTION(BlueprintCallable, Category = Inventory)
	void GetInventoryItems(TArray<USItem*>& Items, FPrimaryAssetType ItemType);

	/** Returns number of instances of this item found in the inventory. This uses count from GetItemData */
	UFUNCTION(BlueprintPure, Category = Inventory)
	int32 GetInventoryItemCount(USItem* Item) const;

	/** Returns the item data associated with an item. Returns false if none found */
	UFUNCTION(BlueprintPure, Category = Inventory)
	bool GetInventoryItemData(USItem* Item, FSItemData& ItemData) const;

	/** Sets slot to item, will remove from other slots if necessary. If passing null this will empty the slot */
	UFUNCTION(BlueprintCallable, Category = Inventory)
	bool SetSlottedItem(FSItemSlot ItemSlot, USItem* Item);

	/** Returns item in slot, or null if empty */
	UFUNCTION(BlueprintPure, Category = Inventory)
	USItem* GetSlottedItem(FSItemSlot ItemSlot) const;

	/** Returns all slotted items of a given type. If none is passed as type it will return all */
	UFUNCTION(BlueprintCallable, Category = Inventory)
	void GetSlottedItems(TArray<USItem*>& Items, FPrimaryAssetType ItemType, bool bOutputEmptyIndexes);

	/** Fills in any empty slots with items in inventory */
	UFUNCTION(BlueprintCallable, Category = Inventory)
	void FillEmptySlots();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Calls AddDefaultInventory when this controller posses the pawn. */
	virtual void OnPossess(APawn* InPawn) override;

	/** Populates InventoryData and SlottedItems. */
	void AddDefaultInventory();
	
	/** Auto slots a specific item, returns true if anything changed */
	bool FillEmptySlotWithItem(USItem* NewItem);

	/** Calls the inventory update callbacks */
	void NotifyInventoryItemChanged(bool bAdded, USItem* Item);
	void NotifySlottedItemChanged(FSItemSlot ItemSlot, USItem* Item);

	UFUNCTION(BlueprintCallable)
	void NotifyInventoryLoaded() const;
};
