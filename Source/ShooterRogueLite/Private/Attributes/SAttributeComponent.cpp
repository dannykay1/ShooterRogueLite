﻿// Copyright Danny Kay 2021


#include "Attributes/SAttributeComponent.h"
#include "Engine/DataTable.h"
#include "UObject/ConstructorHelpers.h"


// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> Tables(TEXT("DataTable'/Game/Data/Attributes/DT_Default.DT_Default'"));
	AttributeTable = Tables.Object;
}

// Called when the game starts
void USAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	if (ensure(AttributeTable))
	{
		TArray<FAttribute*> Rows;
		AttributeTable->GetAllRows("", Rows);

		for (int32 i = 0; i < Rows.Num(); i++)
		{
			FGameplayTag Tag = Rows[i]->Tag;
			const float Value = Rows[i]->BaseValue;

			Attributes.Add(Tag, FAttribute(Tag, Value));
		}
	}
}

// Called every frame
void USAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USAttributeComponent::ModifyAttribute(FGameplayTag Tag, float Delta)
{
	for (auto& Attribute : Attributes)
	{
		if (Attribute.Key.MatchesTagExact(Tag))
		{
			Attribute.Value.ModifyValue(Delta);
			OnAttributeChanged.Broadcast(Attribute.Value);
		}
	}
}
