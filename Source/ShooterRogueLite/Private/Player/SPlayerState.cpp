// Copyright Danny Kay 2021


#include "Player/SPlayerState.h"

#include <wincodec.h>


// Sets default values
ASPlayerState::ASPlayerState()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASPlayerState::BeginPlay()
{
	Super::BeginPlay();	
}

bool ASPlayerState::HasEnoughCredits(int32 Delta) const
{
	return Credits >= Delta;
}

void ASPlayerState::AddCredits(int32 Delta)
{
	// Check for trying to add negative numbers
	if (!ensure(Delta > 0))
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot add negative credits %d"), Delta);
		return;
	}
	
	Credits += Delta;

	OnCreditsChanged.Broadcast(this, Credits, Delta);
}

bool ASPlayerState::RemoveCredits(int32 Delta)
{
	if (!ensure(Delta > 0))
	{
		return false;
	}

	if (!HasEnoughCredits(Delta))
	{
		return false;
	}
	
	Credits -= Delta;
	
	OnCreditsChanged.Broadcast(this, Credits, Delta);
	
	return true;
}