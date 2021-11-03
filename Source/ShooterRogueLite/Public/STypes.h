// Copyright Danny Kay 2021

#pragma once

// Copyright Danny Kay 2021

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataTable.h"
#include "STypes.generated.h"

USTRUCT(BlueprintType)
struct SHOOTERROGUELITE_API FAttribute : public FTableRowBase
{
	GENERATED_BODY()

	FAttribute()
	{
		CurrentValue = BaseValue = 0.f;
	}

	FAttribute(FGameplayTag DefaultTag, float DefaultValue)
	{
		Tag = DefaultTag;
		CurrentValue = BaseValue = DefaultValue;
	}

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag Tag;

	UPROPERTY(BlueprintReadOnly)
	float CurrentValue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float BaseValue;

	bool MatchesTagExact(FGameplayTag TagToCompare) const
	{
		return Tag.MatchesTagExact(TagToCompare);
	}

	void ModifyValue(float Delta)
	{
		CurrentValue = FMath::Clamp(CurrentValue + Delta, 0.f, BaseValue);
	}
};

USTRUCT(BlueprintType)
struct SHOOTERROGUELITE_API FDamageInfo
{
	GENERATED_BODY()

	FDamageInfo()
	{
		
	}

	
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChanged, FAttribute, Attribute);