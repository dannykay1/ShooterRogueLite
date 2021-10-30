﻿// Copyright Danny Kay 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SPlayerController.generated.h"

UCLASS()
class SHOOTERROGUELITE_API ASPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASPlayerController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};