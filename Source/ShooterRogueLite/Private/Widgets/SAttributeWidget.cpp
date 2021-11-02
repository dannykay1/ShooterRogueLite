// Copyright Danny Kay 2021


#include "Widgets/SAttributeWidget.h"
#include "Attributes/SAttributeComponent.h"


void USAttributeWidget::InitializeWidget(USAttributeComponent* AttributeComp, FGameplayTag Tag)
{
	if (!ensure(AttributeComp))
	{
		UE_LOG(LogTemp, Warning, TEXT("Attribute Comp is NULL for tag %s"), *Tag.ToString());
		return;
	}
	
	AttributeComponent = AttributeComp;
	AttributeTag = Tag;
}
