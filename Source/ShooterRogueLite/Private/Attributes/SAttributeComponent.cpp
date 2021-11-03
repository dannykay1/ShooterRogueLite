// Copyright Danny Kay 2021


#include "Attributes/SAttributeComponent.h"
#include "Engine/DataTable.h"
#include "UObject/ConstructorHelpers.h"


// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> Tables(TEXT("DataTable'/Game/Data/Attributes/DT_Default.DT_Default'"));
	AttributeTable = Tables.Object;

	DamageTag = FGameplayTag::RequestGameplayTag(FName("Attribute.Damage"));
}

// Called when the game starts
void USAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	if (ensure(AttributeTable))
	{
		Attributes.Empty();

		TArray<FAttribute*> Rows;
		AttributeTable->GetAllRows("", Rows);

		for (int32 i = 0; i < Rows.Num(); i++)
		{
			FGameplayTag Tag = Rows[i]->Tag;
			const float StartValue = Rows[i]->CurrentValue;
			const float MaxValue = Rows[i]->MaximumValue;

			Attributes.Add(Tag, FAttribute(Tag, StartValue, MaxValue));
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
		// if (Attribute.Key.MatchesTagExact(DamageTag))
		// {
		// }
		// else if (Attribute.Key.MatchesTagExact(Tag))
		// {
		// 	Attribute.Value.ModifyValue(Delta);
		// 	OnAttributeChanged.Broadcast(Attribute.Value);
		// }

		if (Attribute.Key.MatchesTagExact(Tag))
		{
			Attribute.Value.ModifyValue(Delta);
			OnAttributeChanged.Broadcast(Attribute.Value);
		}
	}
}
