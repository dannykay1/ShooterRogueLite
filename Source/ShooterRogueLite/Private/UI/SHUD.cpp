// Copyright Danny Kay 2021


#include "UI/SHUD.h"


// Sets default values
ASHUD::ASHUD()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASHUD::BeginPlay()
{
	Super::BeginPlay();
}