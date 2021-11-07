// Copyright Danny Kay 2021

#pragma once

// Copyright Danny Kay 2021

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/PrimaryAssetId.h"
#include "Engine/DataTable.h"
#include "STypes.generated.h"

class USItem;

USTRUCT(BlueprintType)
struct SHOOTERROGUELITE_API FAttribute : public FTableRowBase
{
	GENERATED_BODY()

	FAttribute()
		: CurrentValue(0.f)
		, MaximumValue(0.f)
	{}

	FAttribute(FGameplayTag DefaultTag, float StartingValue, float MaxValue)
		: Tag(DefaultTag)
		, CurrentValue(StartingValue)
		, MaximumValue(MaxValue)
	{}

	/** Gameplay tag used to identify the attribute. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag Tag;

	/** Value of this attribute, clamped between 0 - MaximumValue. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float CurrentValue;

	/** Maximum value for this attribute. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaximumValue;

	/** Quality of life function to compare tags. */
	bool MatchesTagExact(FGameplayTag TagToCompare) const
	{
		return Tag.MatchesTagExact(TagToCompare);
	}

	/** Modifies the attribute, clamps between 0 - MaximumValue. */
	void ModifyValue(const float Delta)
	{
		CurrentValue = FMath::Clamp(CurrentValue + Delta, 0.f, MaximumValue);
	}
};

/* Represents slots for any item, shown in UI. */
USTRUCT(BlueprintType)
struct SHOOTERROGUELITE_API FSItemSlot
{
	GENERATED_BODY()

	FSItemSlot()
		: SlotNumber(-1)
	{
	}

	FSItemSlot(const FPrimaryAssetType& InItemType, int32 InSlotNumber)
		: ItemType(InItemType)
		, SlotNumber(InSlotNumber)
	{
	}

	/** The type of items that can go in this slot */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	FPrimaryAssetType ItemType;

	/** The number of this slot, 0 indexed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	int32 SlotNumber;

	bool IsValid() const
	{
		return ItemType.IsValid() && SlotNumber >= 0;
	}

	/** Equality operators */
	bool operator==(const FSItemSlot& Other) const
	{
		return ItemType == Other.ItemType && SlotNumber == Other.SlotNumber;
	}

	bool operator!=(const FSItemSlot& Other) const
	{
		return !(*this == Other);
	}

	/** Implemented so it can be used in Maps/Sets */
	friend inline uint32 GetTypeHash(const FSItemSlot& Key)
	{
		uint32 Hash = 0;

		Hash = HashCombine(Hash, GetTypeHash(Key.ItemType));
		Hash = HashCombine(Hash, (uint32)Key.SlotNumber);
		return Hash;
	}
};

/** Extra information about a USItem that is in a player's inventory */
USTRUCT(BlueprintType)
struct SHOOTERROGUELITE_API FSItemData
{
	GENERATED_BODY()

	/** Constructor, default to count/level 1 so declaring them in blueprints gives you the expected behavior */
	FSItemData()
		: ItemCount(0)
	{
	}

	FSItemData(int32 InItemCount)
		: ItemCount(InItemCount)
	{
	}

	/** The number of instances of this item in the inventory, can never be below 1 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	int32 ItemCount;

	/** Returns true if count is greater than 0 */
	bool IsValid() const
	{
		return ItemCount > 0;
	}

	void UpdateItemData(const FSItemData& Other, int32 MaxCount)
	{
		if (MaxCount <= 0)
		{
			MaxCount = MAX_int32;
		}

		ItemCount = FMath::Clamp(ItemCount + Other.ItemCount, 1, MaxCount);
	}

	void UpdateItemData(const int32 Delta, int32 MaxCount)
	{
		if (MaxCount <= 0)
		{
			MaxCount = MAX_int32;
		}

		ItemCount = FMath::Clamp(ItemCount + Delta, 1, MaxCount);
	}

	/** Equality operators */
	bool operator==(const FSItemData& Other) const
	{
		return ItemCount == Other.ItemCount;
	}

	bool operator!=(const FSItemData& Other) const
	{
		return !(*this == Other);
	}
};

/** Called when an attribute has been changed. */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChanged, FAttribute, Attribute);

/** Delegate called when an inventory item changes */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInventoryItemChanged, bool, bAdded, USItem*, Item);

/** Delegate called when the contents of an inventory slot change */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSlottedItemChanged, FSItemSlot, ItemSlot, USItem*, Item);

/** Delegate called when the entire inventory has been loaded, all items may have been replaced */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryLoaded);

UENUM(BlueprintType)
enum class EItemRarity : uint8
{
	Common		UMETA(DisplayName = "Common"),
	Uncommon	UMETA(DisplayName = "Uncommon"),
	Rare		UMETA(DisplayName = "Rare"),
	Legendary	UMETA(DisplayName = "Legendary")
};
