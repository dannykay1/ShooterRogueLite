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

bool USBlueprintLibrary::ApplyDamage(AActor* DamagedActor, float BaseDamage, AController* EventInstigator, AActor* DamageCauser, TSubclassOf<USDamageType> DamageType)
{
	if (!DamagedActor)
	{
		return false;
	}

	if (USAttributeComponent* AttributeComp = GetAttributeComponent(DamagedActor))
	{
		BaseDamage = FMath::Abs(BaseDamage);

		AttributeComp->ModifyHealthAttribute(-BaseDamage);

		const FText DisplayText = FText::AsNumber(BaseDamage);

		SpawnFloatingText(DamagedActor, DamageType, DamagedActor->GetActorLocation(), DisplayText);
		return true;
	}

	return false;
}

bool USBlueprintLibrary::ApplyPointDamage(AActor* DamagedActor, float BaseDamage, FVector HitLocation, AController* EventInstigator, AActor* DamageCauser,
                                          TSubclassOf<USDamageType> DamageType)
{
	if (!DamagedActor)
	{
		return false;
	}

	if (USAttributeComponent* AttributeComp = GetAttributeComponent(DamagedActor))
	{
		BaseDamage = FMath::Abs(BaseDamage);

		AttributeComp->ModifyHealthAttribute(-BaseDamage);

		const FText DisplayText = FText::AsNumber(BaseDamage);

		SpawnFloatingText(DamagedActor, DamageType, HitLocation, DisplayText);
		return true;
	}

	return false;
}

ASHUD* USBlueprintLibrary::GetHUD(const AActor* Caller)
{
	if (!Caller)
	{
		return nullptr;
	}

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(Caller->GetWorld(), 0);
	if (PlayerController)
	{
		return Cast<ASHUD>(PlayerController->GetHUD());
	}

	return nullptr;
}

void USBlueprintLibrary::SpawnFloatingText(AActor* Caller, TSubclassOf<USDamageType> DamageType, FVector Location, FText DisplayText)
{
	if (!DamageType)
	{
		return;
	}

	if (ASHUD* HUD = GetHUD(Caller))
	{
		HUD->SpawnFloatingText(DamageType, Location, DisplayText);
	}
}
