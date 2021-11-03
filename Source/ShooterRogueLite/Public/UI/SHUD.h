// Copyright Danny Kay 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SHUD.generated.h"

class USDamageType;
class USFloatingTextWidget;

UCLASS()
class SHOOTERROGUELITE_API ASHUD : public AHUD
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASHUD();

	UFUNCTION(BlueprintImplementableEvent, Category = FloatingText)
	void SpawnFloatingText(TSubclassOf<USDamageType> DamageType, const FVector Location, const FText& DisplayText);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
