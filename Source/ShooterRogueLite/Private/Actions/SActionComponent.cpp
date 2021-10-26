// Copyright Danny Kay 2021


#include "Actions/SActionComponent.h"
#include "Actions/SAction.h"


// Sets default values for this component's properties
USActionComponent::USActionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void USActionComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void USActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool USActionComponent::HasActiveTag(FGameplayTagContainer Tags) const
{
	return ActiveGameplayTags.HasAny(Tags);
}

void USActionComponent::AddAction(TSubclassOf<USAction> ActionClass)
{
	if (!ensure(ActionClass))
	{
		return;
	}

	USAction* NewAction = NewObject<USAction>(this, ActionClass);
	if (ensure(NewAction))
	{
		NewAction->Initialize(this);
		Actions.Add(NewAction);
	}
}

bool USActionComponent::StartAction(AActor* Instigator, FGameplayTag ActionTag)
{
	for (USAction* Action : Actions)
	{
		if (Action && Action->AbilityTag.MatchesTagExact(ActionTag))
		{
			Action->StartAction(Instigator);
			return true;
		}
	}

	return false;
}

bool USActionComponent::StopAction(AActor* Instigator, FGameplayTag ActionTag)
{
	for (USAction* Action : Actions)
	{
		if (Action && Action->AbilityTag.MatchesTagExact(ActionTag))
		{
			Action->StopAction(Instigator);
			return true;
		}
	}

	return false;
}
