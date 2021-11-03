// Copyright Danny Kay 2021


#include "DamageTypes/SFloatingText.h"


// Sets default values
ASFloatingText::ASFloatingText()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Color = FLinearColor::White;
	Text = FText::FromString("Default Text");
}

// Called when the game starts or when spawned
void ASFloatingText::BeginPlay()
{
	Super::BeginPlay();
}

