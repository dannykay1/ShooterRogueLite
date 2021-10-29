// Copyright Danny Kay 2021


#include "Actions/SAttributeComponent.h"


// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
}

// Called when the game starts
void USAttributeComponent::BeginPlay()
{
	Super::BeginPlay();
	
	for (TPair<FGameplayTag, FAttribute>& Pair : Attributes)
	{
		Pair.Value.Initialize();
	}
}

// Called every frame
void USAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool USAttributeComponent::ModifyAttribute(FGameplayTag Tag, float Delta, FAttribute& Attribute)
{
	for (TPair<FGameplayTag, FAttribute>& Pair : Attributes)
	{
		if (Pair.Key.MatchesTagExact(Tag))
		{
			Pair.Value.ModifyValue(Delta);
			Attribute = Pair.Value;
			OnAttributeChanged.Broadcast(Tag, Pair.Value);
			return true;
		}
	}

	return false;
}
