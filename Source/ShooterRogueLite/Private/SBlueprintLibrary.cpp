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
	if (USActionComponent* ActionComp = GetActionComponent(Actor))
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

bool USBlueprintLibrary::ApplyDamage(AActor* DamagedActor, FGameplayTag Tag, float BaseDamage, AController* EventInstigator, AActor* DamageCauser,
                                     TSubclassOf<UDamageType> DamageType)
{
	if (USAttributeComponent* AttributeComp = GetAttributeComponent(DamagedActor))
	{
		AttributeComp->ModifyAttribute(Tag, DamagedActor->GetActorLocation(), -BaseDamage);
		return true;
	}

	return false;
}

bool USBlueprintLibrary::ApplyPointDamage(AActor* DamagedActor, FGameplayTag Tag, float BaseDamage, FVector HitLocation, AController* EventInstigator, AActor* DamageCauser,
                                          TSubclassOf<UDamageType> DamageType)
{
	if (USAttributeComponent* AttributeComp = GetAttributeComponent(DamagedActor))
	{
		AttributeComp->ModifyAttribute(Tag, HitLocation, -BaseDamage);
		return true;
	}

	return false;
}
