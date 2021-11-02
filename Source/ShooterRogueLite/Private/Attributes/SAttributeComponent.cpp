// Copyright Danny Kay 2021


#include "Attributes/SAttributeComponent.h"
#include "Attributes/SStartingAttributesData.h"


// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	// Health = FAttribute(FGameplayTag::RequestGameplayTag("Attribute.Health"), 100.f);
	// Armor = FAttribute(FGameplayTag::RequestGameplayTag("Attribute.Armor"), 100.f);
	// Speed = FAttribute(FGameplayTag::RequestGameplayTag("Attribute.Speed"), 600.f);
	// Credits = FAttribute(FGameplayTag::RequestGameplayTag("Attribute.Credits"), 50000.f);
	// Experience = FAttribute(FGameplayTag::RequestGameplayTag("Attribute.Experience"), 100.f);
}

// Called when the game starts
void USAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	if (ensureAlways(DefaultAttribute))
	{
		Attributes.Empty();

		for (auto& Attribute : DefaultAttribute->Attributes)
		{
			Attributes.Add(Attribute.Key, FAttribute(Attribute.Key, Attribute.Value.BaseValue));
		}
	}
}

// Called every frame
void USAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USAttributeComponent::ModifyAttribute(FGameplayTag Tag, float Delta)
{
	for (auto& Attribute : Attributes)
	{
		if (Attribute.Key.MatchesTagExact(Tag))
		{
			Attribute.Value.ModifyValue(Delta);
			OnAttributeChanged.Broadcast(Attribute.Value);
		}
	}
}
