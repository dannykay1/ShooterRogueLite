// Copyright Danny Kay 2021


#include "SBlueprintLibrary.h"
#include "Actions/SActionComponent.h"


USActionComponent* USBlueprintLibrary::GetActionComponent(AActor* Actor) const
{
	if (Actor)
	{
		return Cast<USActionComponent>(Actor->GetComponentByClass(USActionComponent::StaticClass()));
	}

	return nullptr;
}

bool USBlueprintLibrary::ActorHasTag(AActor* Actor, FGameplayTag Tag) const
{
	USActionComponent* ActionComp = GetActionComponent(Actor);
	if (ActionComp)
	{
		return ActionComp->ActiveGameplayTags.HasTagExact(Tag);
	}
	
	return false;
}
