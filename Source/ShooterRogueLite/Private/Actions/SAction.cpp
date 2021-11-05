// Copyright Danny Kay 2021


#include "Actions/SAction.h"
#include "Actions/SActionComponent.h"
#include "GameFramework/Actor.h"


USAction::USAction()
{
	bIsRunning = false;
	bAutoStart = false;
}

void USAction::Initialize(USActionComponent* NewActionComp)
{
	ActionComp = NewActionComp;
}

UWorld* USAction::GetWorld() const
{
	AActor* Actor = Cast<AActor>(GetOuter());
	return Actor ? Actor->GetWorld() : nullptr;
}

bool USAction::CanActivateAction(AActor* Instigator)
{
	if (GetIsRunning())
	{
		return false;
	}
	
	USActionComponent* Comp = GetOwningComponent();

	return !Comp->ActiveGameplayTags.HasAny(BlockAbilitiesWithTag) && CanStart(Instigator);
}

bool USAction::CanStart_Implementation(AActor* Instigator)
{
	return true;
}

void USAction::StartAction(AActor* Instigator)
{
	USActionComponent* Comp = GetOwningComponent();
	Comp->ActiveGameplayTags.AppendTags(GrantedTags);
	
	bIsRunning = true;
	
	OnStartAction(Instigator);
}

void USAction::StopAction(AActor* Instigator)
{
	ensureAlways(bIsRunning);
	
	USActionComponent* Comp = GetOwningComponent();
	Comp->ActiveGameplayTags.RemoveTags(GrantedTags);

	bIsRunning = false;
	
	OnStopAction(Instigator);
}
