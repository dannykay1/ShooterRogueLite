// Copyright Danny Kay 2021


#include "Framework/SGameModeBase.h"


// Sets default values
ASGameModeBase::ASGameModeBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

