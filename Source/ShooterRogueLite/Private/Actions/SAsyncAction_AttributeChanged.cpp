// Copyright Danny Kay 2021


#include "Actions/SAsyncAction_AttributeChanged.h"
#include "Attributes/SAttributeComponent.h"


USAsyncAction_AttributeChanged* USAsyncAction_AttributeChanged::ListenForAttributeChange(USAttributeComponent* AttributeComponent, FGameplayTag Tag)
{
	if (!ensure(AttributeComponent))
	{
		UE_LOG(LogTemp, Error, TEXT("Attribute component is nullptr!"));
		return nullptr;
	}
	
	USAsyncAction_AttributeChanged* WaitTask = NewObject<USAsyncAction_AttributeChanged>();
	WaitTask->AttributeComponent = AttributeComponent;
	WaitTask->TagToListenFor = Tag;

	AttributeComponent->OnAttributeChanged.AddDynamic(WaitTask, &USAsyncAction_AttributeChanged::AttributeChanged);

	return WaitTask;
}

void USAsyncAction_AttributeChanged::EndTask()
{
	if (ensure(AttributeComponent))
	{
		AttributeComponent->OnAttributeChanged.RemoveAll(this);
	}

	SetReadyToDestroy();
	MarkPendingKill();
}

void USAsyncAction_AttributeChanged::AttributeChanged(const FAttribute Attribute)
{
	if (TagToListenFor.MatchesTagExact(Attribute.Tag))
	{
		OnAttributeChanged.Broadcast(Attribute);
	}
}
