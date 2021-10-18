// Copyright Danny Kay 2021

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "SAbilitySystemComponent.generated.h"

class USGameplayAbility;
class UInputComponent;

/**
 * Base class for any actor that needs to have abilities.
 */
UCLASS()
class SHOOTERROGUELITE_API USAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	/** Constructor to set default values */
	USAbilitySystemComponent();
	
	void GiveStartingAbilities();
	void GiveDefaultAttribute();
	void BindASCInput(UInputComponent* InputComponent);

protected:
	/** Starting abilities */
	UPROPERTY(EditDefaultsOnly, Category = Abilities)
	TArray<TSubclassOf<USGameplayAbility>> StartingAbilities;

	/** Default attributes for a character for initializing on spawn/respawn. */
	UPROPERTY(EditDefaultsOnly, Category = Abilities)
	TSubclassOf<UGameplayEffect> StartingAttribute;

	bool bInputBound;
};
