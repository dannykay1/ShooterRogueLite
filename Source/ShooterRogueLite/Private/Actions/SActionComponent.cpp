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

	for (const TSubclassOf<USAction> ActionClass : DefaultActions)
	{
		AddAction(GetOwner(), ActionClass);
	}
}

// Called every frame
void USActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FString Msg = GetNameSafe(GetOwner()) + ": " + ActiveGameplayTags.ToStringSimple();

	//GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Yellow, Msg);
}

void USActionComponent::AddAction(AActor* Instigator, TSubclassOf<USAction> ActionClass)
{
	if (!ensure(ActionClass))
	{
		return;
	}

	USAction* NewAction = NewObject<USAction>(GetOwner(), ActionClass);
	if (ensure(NewAction))
	{
		NewAction->Initialize(this);
		Actions.Add(NewAction);

		if (NewAction->bAutoStart && ensure(NewAction->CanActivateAction(Instigator)))
		{
			NewAction->StartAction(Instigator);
		}
	}
}

void USActionComponent::RemoveAction(USAction* ActionToRemove)
{
	if (ensure(ActionToRemove && !ActionToRemove->GetIsRunning()))
	{
		Actions.Remove(ActionToRemove);
	}
}

bool USActionComponent::StartAction(AActor* Instigator, FGameplayTag ActionTag)
{
	for (USAction* Action : Actions)
	{
		if (Action && Action->AbilityTag.MatchesTagExact(ActionTag))
		{
			CancelAbilitiesWithTags(Instigator, Action->CancelAbilitiesWithTag);

			if (!Action->CanActivateAction(Instigator))
			{
				FString FailedMsg = FString::Printf(TEXT("Failed to run: %s"), *ActionTag.ToString());
				GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FailedMsg);
				continue;
			}

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
			if (Action->GetIsRunning())
			{
				Action->StopAction(Instigator);
				return true;
			}
		}
	}

	return false;
}

void USActionComponent::CancelAbilitiesWithTags(AActor* Instigator, FGameplayTagContainer Tags)
{
	for (USAction* Action : Actions)
	{
		if (Action && ActiveGameplayTags.HasAny(Tags))
		{
			if (Action->GetIsRunning())
			{
				FString FailedMsg = FString::Printf(TEXT("Cancelled: %s"), *Action->AbilityTag.ToString());
				GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FailedMsg);

				Action->StopAction(Instigator);
			}
		}
	}
}
