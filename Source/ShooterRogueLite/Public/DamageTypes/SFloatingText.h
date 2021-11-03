// Copyright Danny Kay 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SFloatingText.generated.h"

UCLASS()
class SHOOTERROGUELITE_API ASFloatingText : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASFloatingText();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = Text, meta = (ExposeOnSpawn))
	FLinearColor Color;

	UPROPERTY(BlueprintReadOnly, Category = Text, meta = (ExposeOnSpawn))
	FText Text;
};
