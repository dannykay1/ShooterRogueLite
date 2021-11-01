// Copyright Danny Kay 2021


#include "Widgets/SInteractionWidget.h"
#include "Widgets/SInteractionWidgetComponent.h"


void USInteractionWidget::UpdateInteractionWidget(USInteractionWidgetComponent* InteractionComponent)
{
    OwningInteractionComponent = InteractionComponent;
    OnUpdateInteractionWidget();
}
