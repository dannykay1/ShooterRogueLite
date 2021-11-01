// Copyright Danny Kay 2021


#include "SBlueprintLibrary.h"
#include "Actions/SActionComponent.h"
#include "Attributes/SAttributeComponent.h"


USActionComponent* USBlueprintLibrary::GetActionComponent(AActor* Actor)
{
	if (Actor)
	{
		return Cast<USActionComponent>(Actor->GetComponentByClass(USActionComponent::StaticClass()));
	}

	return nullptr;
}

bool USBlueprintLibrary::ActorHasTag(AActor* Actor, FGameplayTag Tag)
{
	USActionComponent* ActionComp = GetActionComponent(Actor);
	if (ActionComp)
	{
		return ActionComp->ActiveGameplayTags.HasTagExact(Tag);
	}

	return false;
}

USAttributeComponent* USBlueprintLibrary::GetAttributeComponent(AActor* Actor)
{
	if (Actor)
	{
		return Cast<USAttributeComponent>(Actor->GetComponentByClass(USAttributeComponent::StaticClass()));
	}

	return nullptr;
}
