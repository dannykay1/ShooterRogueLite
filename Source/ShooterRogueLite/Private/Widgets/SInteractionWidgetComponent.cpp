// Copyright Danny Kay 2021


#include "Widgets/SInteractionWidgetComponent.h"
#include "Components/SInteractionComponent.h"
#include "Player/SPlayerCharacter.h"
#include "Widgets/SInteractionWidget.h"


// Sets default values for this component's properties
USInteractionWidgetComponent::USInteractionWidgetComponent()
{
	SetComponentTickEnabled(false);

	InteractionTime = 0.f;
	InteractionDistance = 200.f;
	InteractableNameText = FText::FromString("Interactable Object");
	InteractableActionText = FText::FromString("Interact");

	Space = EWidgetSpace::Screen;
	DrawSize = FIntPoint(600, 100);
	bDrawAtDesiredSize = true;

	SetActive(true);
	SetHiddenInGame(true);
}

void USInteractionWidgetComponent::Deactivate()
{
	Super::Deactivate();

	if (Interactor)
	{
		EndFocus(Interactor);
		EndInteract(Interactor);
	}

	Interactor = nullptr;
}

void USInteractionWidgetComponent::RefreshWidget()
{
	if (!bHiddenInGame)
	{
		if (USInteractionWidget* InteractionWidget = Cast<USInteractionWidget>(GetUserWidgetObject()))
		{
			InteractionWidget->UpdateInteractionWidget(this);
		}
	}
}

void USInteractionWidgetComponent::SetInteractableNameText(const FText& NewNameText)
{
	InteractableNameText = NewNameText;
	RefreshWidget();
}

void USInteractionWidgetComponent::SetInteractableActionText(const FText& NewActionText)
{
	InteractableActionText = NewActionText;
	RefreshWidget();
}

float USInteractionWidgetComponent::GetInteractPercentage() const
{
	if (!Interactor)
		return 0.f;
	
	USInteractionComponent* InteractionComponent = Cast<USInteractionComponent>(Interactor->GetComponentByClass(USInteractionComponent::StaticClass()));

	if(!InteractionComponent)
		return 0.f;

	return 1.f - FMath::Abs(InteractionComponent->GetRemainingInteractionTime() / InteractionTime);
}

bool USInteractionWidgetComponent::CanInteract(ASPlayerCharacter* Character) const
{
	return IsActive() && GetOwner() && Character;
}

void USInteractionWidgetComponent::BeginFocus(ASPlayerCharacter* Character)
{
	if (!GetOwner() || !Character)
		return;

	OnBeginFocus.Broadcast(Character);

	SetHiddenInGame(false);

	TArray<UPrimitiveComponent*> PrimitiveComponents;
	GetOwner()->GetComponents(PrimitiveComponents);

	for (auto& VisualComp : PrimitiveComponents)
	{
		if (UPrimitiveComponent* Prim = Cast<UPrimitiveComponent>(VisualComp))
		{
			Prim->SetRenderCustomDepth(true);
		}
	}
	
	RefreshWidget();
}

void USInteractionWidgetComponent::EndFocus(ASPlayerCharacter* Character)
{
	if (!GetOwner() || !Character)
		return;

	OnEndFocus.Broadcast(Character);

	SetHiddenInGame(true);

	TArray<UPrimitiveComponent*> PrimitiveComponents;
	GetOwner()->GetComponents(PrimitiveComponents);

	for (auto& VisualComp : PrimitiveComponents)
	{
		if (UPrimitiveComponent* Prim = Cast<UPrimitiveComponent>(VisualComp))
		{
			Prim->SetRenderCustomDepth(false);
		}
	}
}

void USInteractionWidgetComponent::BeginInteract(ASPlayerCharacter* Character)
{
	if (CanInteract(Character))
	{
		Interactor = Character;
		OnBeginInteract.Broadcast(Character);
	}
}

void USInteractionWidgetComponent::EndInteract(ASPlayerCharacter* Character)
{
	Interactor = nullptr;
	OnEndInteract.Broadcast(Character);
}

void USInteractionWidgetComponent::Interact(ASPlayerCharacter* Character) const
{
	if (CanInteract(Character))
	{
		OnInteract.Broadcast(Character);
	}
}
