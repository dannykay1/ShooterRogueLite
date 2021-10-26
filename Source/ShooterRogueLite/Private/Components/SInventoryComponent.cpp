// Copyright Danny Kay 2021


#include "Components/SInventoryComponent.h"
#include "Weapons/SWeapon.h"


// Sets default values for this component's properties
USInventoryComponent::USInventoryComponent()
{
	WeaponIndex = 0;
}

// Called when the game starts
void USInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

ASWeapon* USInventoryComponent::GetCurrentWeapon() const
{
	return Weapons.IsValidIndex(WeaponIndex) ? Weapons[WeaponIndex] : nullptr;
}

void USInventoryComponent::NextWeapon()
{
	if (WeaponIndex + 1 <= Weapons.Num() - 1)
	{
		WeaponIndex++;
	}
	else
	{
		WeaponIndex = 0;
	}
}

void USInventoryComponent::PreviousWeapon()
{
	if (WeaponIndex - 1 <= 0)
	{
		WeaponIndex--;
	}
	else
	{
		WeaponIndex = Weapons.Num() - 1;
	}
}

void USInventoryComponent::SetCurrentWeapon(ASWeapon* NewWeapon)
{
	if (GetCurrentWeapon() && NewWeapon)
	{
		Weapons[WeaponIndex] = NewWeapon;
	}
}

void USInventoryComponent::AddWeapon(ASWeapon* WeaponToAdd)
{
	if (WeaponToAdd)
	{
		Weapons.Add(WeaponToAdd);
	}
}

void USInventoryComponent::RemoveWeapon(ASWeapon* WeaponToRemove)
{
	if (Weapons.Num() > 1 && WeaponToRemove)
	{
		Weapons.Remove(WeaponToRemove);
	}
}
