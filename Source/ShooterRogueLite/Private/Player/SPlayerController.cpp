// Copyright Danny Kay 2021


#include "Player/SPlayerController.h"


// Sets default values
ASPlayerController::ASPlayerController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

