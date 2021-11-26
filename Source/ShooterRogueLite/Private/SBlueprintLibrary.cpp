// Copyright Danny Kay 2021


#include "SBlueprintLibrary.h"
#include "Actions/SActionComponent.h"
#include "Attributes/SAttributeComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "DamageTypes/SDamageType.h"
#include "UI/SHUD.h"


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
	if (const USActionComponent* ActionComp = GetActionComponent(Actor))
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

ASHUD* USBlueprintLibrary::GetHUD(const AActor* WorldActor)
{
	if (!WorldActor)
	{
		return nullptr;
	}

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(WorldActor->GetWorld(), 0);
	if (PlayerController)
	{
		return Cast<ASHUD>(PlayerController->GetHUD());
	}

	return nullptr;
}

void USBlueprintLibrary::SpawnFloatingText(AActor* WorldActor, TSubclassOf<USDamageType> DamageType, FVector Location, FText DisplayText)
{
	if (!DamageType)
	{
		return;
	}

	if (ASHUD* HUD = GetHUD(WorldActor))
	{
		HUD->SpawnFloatingText(DamageType, Location, DisplayText);
	}
}