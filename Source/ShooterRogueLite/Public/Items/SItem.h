// Copyright Danny Kay 2021

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SItem.generated.h"

class UTexture2D;
class USAction;

/**
 * Base class for all items.
 * Meant to be sub-classed and blueprinted.
 */
UCLASS(Abstract, BlueprintType)
class SHOOTERROGUELITE_API USItem : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	/* Sets default values. */
	USItem()
		: ItemName(FText::FromString("Name of the item"))
		, ItemDescription(FText::FromString("Description of what the item does"))
		, MaxCount(1)
	{}

	/* Type of this item, set in native parent class */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item)
	FPrimaryAssetType ItemType;

	/** User-visible short name */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	FText ItemName;

	/** User-visible long description */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	FText ItemDescription;

	/** Icon to display */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	UTexture2D* ItemIcon;

	/** Maximum number of instances that can be in inventory at once, <= 0 means infinite */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Max)
	int32 MaxCount;

	/** Actions to give when equipping this weapon. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Actions)
	TArray<TSubclassOf<USAction>> ActionsToGive;

	/** Returns if the item is consumable (MaxCount <= 0)*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Max)
	FORCEINLINE bool IsConsumable() const { return MaxCount <= 0; }

	/** Returns the logical name, equivalent to the primary asset id */
	UFUNCTION(BlueprintCallable, Category = Item)
	FString GetIdentifierString() const;

	/** Overridden to use saved type */
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};
