// Copyright Danny Kay 2021


#include "Widgets/SAttributeWidget.h"
#include "Actions/SAttributeComponent.h"


void USAttributeWidget::InitializeWidget(USAttributeComponent* AttributeComp, FGameplayTag Tag)
{
	AttributeComponent = AttributeComp;
	AttributeTag = Tag;

	AttributeComponent->OnAttributeChanged.AddDynamic(this, &USAttributeWidget::AttributeChanged);
}

void USAttributeWidget::AttributeChanged(FAttribute Attribute, float Delta)
{
	if (Attribute.Tag.MatchesTagExact(AttributeTag))
	{
		OnAttributeChanged(Attribute, Delta);
	}
}
