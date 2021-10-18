// Copyright Danny Kay 2021

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "ShooterRogueLite/ShooterRogueLite.h"
#include "SGameplayAbility.generated.h"

/**
 * Base class for game play abilities that can be auto mapped to player input.
 */
UCLASS()
class SHOOTERROGUELITE_API USGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	EAbilityInputID InputID;
};
