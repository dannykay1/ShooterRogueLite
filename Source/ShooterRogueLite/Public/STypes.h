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
		CurrentValue = MaximumValue = 0.f;
	}

	// FAttribute(FString TagName, float DefaultValue)
	// {
	// 	Tag = FGameplayTag::RequestGameplayTag(FName(*TagName));
	// 	CurrentValue = BaseValue = DefaultValue;
	// }
	//
	// FAttribute(FGameplayTag DefaultTag, float DefaultValue)
	// {
	// 	Tag = DefaultTag;
	// 	CurrentValue = BaseValue = DefaultValue;
	// }

	FAttribute(FGameplayTag DefaultTag, float StartingValue, float MaxValue)
	{
		Tag = DefaultTag;
		CurrentValue = StartingValue;
		MaximumValue = MaxValue;
	}

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag Tag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float CurrentValue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MaximumValue;

	bool MatchesTagExact(FGameplayTag TagToCompare) const
	{
		return Tag.MatchesTagExact(TagToCompare);
	}

	void ModifyValue(float Delta)
	{
		CurrentValue = FMath::Clamp(CurrentValue + Delta, 0.f, MaximumValue);
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChanged, FAttribute, Attribute);
