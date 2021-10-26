// Copyright Danny Kay 2021


#include "Actions/SAction.h"
#include "Actions/SActionComponent.h"
#include "GameFramework/Actor.h"

USAction::USAction()
{
}

void USAction::Initialize(USActionComponent* NewActionComp)
{
	ActionComp = NewActionComp;
}

USActionComponent* USAction::GetOwningComponent() const
{
	return ActionComp;
}

void USAction::StartAction(AActor* Instigator)
{
	USActionComponent* Comp = GetOwningComponent();
	Comp->ActiveGameplayTags.AppendTags(GrantedTags);
	
	OnStartAction(Instigator);
}

void USAction::StopAction(AActor* Instigator)
{
	USActionComponent* Comp = GetOwningComponent();
	Comp->ActiveGameplayTags.RemoveTags(GrantedTags);
	
	OnStopAction(Instigator);
}
