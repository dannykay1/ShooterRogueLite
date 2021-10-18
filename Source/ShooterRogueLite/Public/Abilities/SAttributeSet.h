// Copyright Danny Kay 2021

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "SAttributeSet.generated.h"

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class SHOOTERROGUELITE_API USAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	/** Initialize default attribute values */
	USAttributeSet();
	
	// Current Health, when 0 we expect owner to die unless prevented by an ability. Capped by MaxHealth.
	// Positive changes can directly use this.
	// Negative changes to Health should go through Damage meta attribute.
	UPROPERTY(BlueprintReadOnly, Category = Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(USAttributeSet, Health)

	// MaxHealth is its own attribute since GameplayEffects may modify it
	UPROPERTY(BlueprintReadOnly, Category = Health)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(USAttributeSet, MaxHealth)

	// Current armor acts like temporary health. When depleted, damage will drain regular health.
	UPROPERTY(BlueprintReadOnly, Category = Shield)
	FGameplayAttributeData Shield;
	ATTRIBUTE_ACCESSORS(USAttributeSet, Shield)

	// Maximum Armor that we can have.
	UPROPERTY(BlueprintReadOnly, Category = Shield)
	FGameplayAttributeData MaxShield;
	ATTRIBUTE_ACCESSORS(USAttributeSet, MaxShield)

	// Damage is a meta attribute used by the DamageExecution to calculate final damage, which then turns into -Health
	UPROPERTY(BlueprintReadOnly, Category = Damage, meta = (HideFromLevelInfos))
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(USAttributeSet, Damage)

	UPROPERTY(BlueprintReadOnly, Category = "Character Level")
	FGameplayAttributeData CharacterLevel;
	ATTRIBUTE_ACCESSORS(USAttributeSet, CharacterLevel)

	// Experience points gained from killing enemies. Used to level up (not implemented in this project).
	UPROPERTY(BlueprintReadOnly, Category = XP)
	FGameplayAttributeData XP;
	ATTRIBUTE_ACCESSORS(USAttributeSet, XP)

	// Experience points awarded to the character's killers. Used to level up (not implemented in this project).
	UPROPERTY(BlueprintReadOnly, Category = XP)
	FGameplayAttributeData XPBounty;
	ATTRIBUTE_ACCESSORS(USAttributeSet, XPBounty)

	// Gold gained from killing enemies. Used to purchase items.
	UPROPERTY(BlueprintReadOnly, Category = Gold)
	FGameplayAttributeData Gold;
	ATTRIBUTE_ACCESSORS(USAttributeSet, Gold)

	// Gold awarded to the character's killer. Used to purchase items (not implemented in this project).
	UPROPERTY(BlueprintReadOnly, Category = Gold)
	FGameplayAttributeData GoldBounty;
	ATTRIBUTE_ACCESSORS(USAttributeSet, GoldBounty)

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

protected:
	// Helper function to proportionally adjust the value of an attribute when it's associated max attribute changes.
	// (i.e. When MaxHealth increases, Health increases by an amount that maintains the same percentage as before)
	void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty) const;
};