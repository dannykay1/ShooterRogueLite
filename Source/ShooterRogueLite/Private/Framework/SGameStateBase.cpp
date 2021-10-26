// Copyright Danny Kay 2021


#include "Framework/SGameStateBase.h"


// Sets default values
ASGameStateBase::ASGameStateBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASGameStateBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASGameStateBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

