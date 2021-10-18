// Copyright Danny Kay 2021


#include "Abilities/SAbilitySystemComponent.h"
#include "Abilities/SGameplayAbility.h"
#include "ShooterRogueLite/ShooterRogueLite.h"

USAbilitySystemComponent::USAbilitySystemComponent()
{
	bInputBound = false;
}

void USAbilitySystemComponent::GiveStartingAbilities()
{
	for (TSubclassOf<USGameplayAbility>& Ability : StartingAbilities)
	{
		if (Ability)
		{
			GiveAbility(FGameplayAbilitySpec(Ability, 1, static_cast<int32>(Ability.GetDefaultObject()->InputID), GetOwner()));
		}
	}
}

void USAbilitySystemComponent::GiveDefaultAttribute()
{
	FGameplayEffectContextHandle EffectContext = MakeEffectContext();
	EffectContext.AddSourceObject(GetOwner());

	const FGameplayEffectSpecHandle NewHandle = MakeOutgoingSpec(StartingAttribute, 1, EffectContext);
	if (NewHandle.IsValid())
	{
		ApplyGameplayEffectSpecToSelf(*NewHandle.Data.Get());
	}
}

void USAbilitySystemComponent::BindASCInput(UInputComponent* InputComponent)
{
	if (InputComponent && !bInputBound)
	{
		bInputBound = true;

		BindAbilityActivationToInputComponent(InputComponent,
		FGameplayAbilityInputBinds(
		FString("Confirm"),
		FString("Cancel"),
		FString("EAbilityInputID"),
		static_cast<int32>(EAbilityInputID::Confirm),
		static_cast<int32>(EAbilityInputID::Cancel)));
	}
}
