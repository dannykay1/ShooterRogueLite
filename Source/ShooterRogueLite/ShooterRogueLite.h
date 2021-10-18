// Copyright Danny Kay 2021

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EAbilityInputID : uint8
{
	// 0 None
	None				UMETA(DisplayName = "None"),
	// 1 Confirm
	Confirm				UMETA(DisplayName = "Confirm"),
	// 2 Cancel
	Cancel				UMETA(DisplayName = "Cancel"),
	// 3 Sprint
	Sprint				UMETA(DisplayName = "Sprint"),
	// 4 Jump
	Jump				UMETA(DisplayName = "Jump"),
	// 5 PrimaryFire
	PrimaryFire			UMETA(DisplayName = "Primary Fire"),
	// 6 ADS
	Aim					UMETA(DisplayName = "Aim Down Sights"),
	// 7 Reload
	Reload				UMETA(DisplayName = "Reload"),
	// 8 NextWeapon
	NextWeapon			UMETA(DisplayName = "Next Weapon"), 
	// 9 PrevWeapon
	PrevWeapon			UMETA(DisplayName = "Previous Weapon"),
	// 10 Interact
	Interact			UMETA(DisplayName = "Interact")
};