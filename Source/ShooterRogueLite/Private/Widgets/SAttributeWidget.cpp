// Copyright Danny Kay 2021


#include "Widgets/SAttributeWidget.h"
#include "Actions/SAttributeComponent.h"


void USAttributeWidget::InitializeWidget(USAttributeComponent* AttributeComp, FGameplayTag Tag)
{
	if (!ensure(AttributeComp))
	{
		UE_LOG(LogTemp, Warning, TEXT("Attribute Comp is NULL for tag %s"), *Tag.ToString());
		return;
	}
	
	AttributeComponent = AttributeComp;
	AttributeTag = Tag;

	AttributeComponent->OnAttributeChanged.AddDynamic(this, &USAttributeWidget::AttributeChanged);
}

void USAttributeWidget::AttributeChanged(FAttribute Attribute, float Delta)
{
	if (Attribute.MatchesTagExact(AttributeTag))
	{
		OnAttributeChanged(Attribute, Delta);
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Widget tryin ta update stuff"));
}
