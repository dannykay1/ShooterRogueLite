// Copyright Danny Kay 2021

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SInventoryComponent.generated.h"

class ASWeapon;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponAdded, ASWeapon*, Weapon);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponRemoved, ASWeapon*, Weapon);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SHOOTERROGUELITE_API USInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/* Weapons owner will start with. */
	UPROPERTY(VisibleAnywhere, Category = Weapons)
	TArray<TSubclassOf<ASWeapon>> StartingWeapons;

	/* All weapons owned by owner. */
	UPROPERTY(VisibleAnywhere, Category = Weapons)
	TArray<ASWeapon*> Weapons;

	/* Current index (equipped) weapon. */
	UPROPERTY(VisibleAnywhere, Category = Weapons)
	int32 WeaponIndex;

public:
	/* Returns current weapon, using WeaponIndex. */
	UFUNCTION(BlueprintPure, Category = Weapons)
	ASWeapon* GetCurrentWeapon() const;

	/* Gets the next weapon in Weapons array. Will loop */
	UFUNCTION(BlueprintCallable, Category = Weapons)
	void NextWeapon();

	/* Gets the previous weapon in weapons array. Will loop. */
	UFUNCTION(BlueprintCallable, Category = Weapons)
	void PreviousWeapon();

	/* Sets the current weapon, ie when picking up a weapon. */
	UFUNCTION(BlueprintCallable, Category = Weapons)
	void SetCurrentWeapon(ASWeapon* NewWeapon);

	/* Adds weapon to weapons array. */
	UFUNCTION(BlueprintCallable, Category = Weapons)
	void AddWeapon(ASWeapon* WeaponToAdd);

	/* Removes weapon to weapons array. */
	UFUNCTION(BlueprintCallable, Category = Weapons)
	void RemoveWeapon(ASWeapon* WeaponToRemove);
};
