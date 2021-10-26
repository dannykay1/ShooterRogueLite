// Copyright Danny Kay 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "SGameStateBase.generated.h"

UCLASS()
class SHOOTERROGUELITE_API ASGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASGameStateBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
