// Copyright Danny Kay 2021

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "SAttributeComponent.generated.h"

class USStartingAttributesData;

USTRUCT(BlueprintType)
struct SHOOTERROGUELITE_API FAttribute
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

	UPROPERTY(BlueprintReadOnly)
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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChanged, FAttribute, Attribute);

/**
* Handles any attributes, defined by FGameplayTag.
*/
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SHOOTERROGUELITE_API USAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USAttributeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/* Sets Attributes from this asset. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Attributes)
	USStartingAttributesData* DefaultAttribute;

	TMap<FGameplayTag, FAttribute> Attributes;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChanged OnAttributeChanged;

	UFUNCTION(BlueprintCallable, Category = Attribute)
	void ModifyAttribute(FGameplayTag Tag, float Delta);
};
