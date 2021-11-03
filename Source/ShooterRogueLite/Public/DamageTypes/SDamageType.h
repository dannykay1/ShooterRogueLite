// Copyright Danny Kay 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "SDamageType.generated.h"

class ASFloatingText;

/**
 * Base damage type class to handle any feedback from taking damage.
 * Will handle showing damage numbers as different damage types will have different number behaviors.
 */
UCLASS(Blueprintable)
class SHOOTERROGUELITE_API USDamageType : public UDamageType
{
	GENERATED_BODY()

public:
	/* Sets default values. */
	USDamageType();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = FloatingText)
	TSubclassOf<ASFloatingText> FloatingTextClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = FloatingText)
	FLinearColor Color;
};
