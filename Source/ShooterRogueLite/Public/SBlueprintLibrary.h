// Copyright Danny Kay 2021

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "SBlueprintLibrary.generated.h"

class USDamageType;
class USActionComponent;
class USAttributeComponent;
class AController;
class UDamageType;
class ASHUD;

/**
 * Game-specific blueprint library.
 * Static functions for quality of life improvements for code and in blueprints. 
 */
UCLASS()
class SHOOTERROGUELITE_API USBlueprintLibrary : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = Game)
	static USActionComponent* GetActionComponent(AActor* Actor);

	UFUNCTION(BlueprintPure, Category = Game)
	static bool ActorHasTag(AActor* Actor, FGameplayTag Tag);

	UFUNCTION(BlueprintPure, Category = Game)
	static USAttributeComponent* GetAttributeComponent(AActor* Actor);

	UFUNCTION(BlueprintCallable, Category = Game)
	static bool ApplyDamage(AActor* DamagedActor, FGameplayTag Tag, float BaseDamage, AController* EventInstigator, AActor* DamageCauser, TSubclassOf<USDamageType> DamageType);

	UFUNCTION(BlueprintCallable, Category = Game)
	static bool ApplyPointDamage(AActor* DamagedActor, FGameplayTag Tag, float BaseDamage, FVector HitLocation, AController* EventInstigator, AActor* DamageCauser,
	                             TSubclassOf<USDamageType> DamageType);

	UFUNCTION(BlueprintPure, Category = Game)
	static ASHUD* GetHUD(const AActor* Caller);

	UFUNCTION(BlueprintCallable, Category = Game)
	static void SpawnFloatingText(AActor* Caller, TSubclassOf<USDamageType> DamageType, FVector Location, FText DisplayText);
};
