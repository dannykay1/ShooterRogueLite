// Copyright Danny Kay 2021


#include "Attributes/SAttributeComponent.h"

#include "SBlueprintLibrary.h"
#include "Engine/DataTable.h"
#include "UObject/ConstructorHelpers.h"


// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UDataTable> Tables(TEXT("DataTable'/Game/Data/Attributes/DT_Default.DT_Default'"));
	AttributeTable = Tables.Object;

	DamageTag = FGameplayTag::RequestGameplayTag(FName("Attribute.Damage"));
}

// Called when the game starts
void USAttributeComponent::BeginPlay()
{
	Super::BeginPlay();
	
	InitializeAttributes();

	if (AActor* MyOwner = GetOwner())
	{
		MyOwner->OnTakeAnyDamage.AddDynamic(this, &USAttributeComponent::OnTakeAnyDamage);
		MyOwner->OnTakePointDamage.AddDynamic(this, &USAttributeComponent::OnTakePointDamage);
		MyOwner->OnTakeRadialDamage.AddDynamic(this, &USAttributeComponent::OnTakeRadialDamage);
	}
}

void USAttributeComponent::InitializeAttributes()
{
	Attributes.Empty();
	
	if (ensure(AttributeTable))
	{	
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

	Attributes.Add(DamageTag, FAttribute(DamageTag, 0.f, 0.f));
}

void USAttributeComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (DamagedActor)
	{
		ModifyHealthAttribute(Damage);

		const FText DisplayText = FText::AsNumber(FMath::Abs(Damage));

		USBlueprintLibrary::SpawnFloatingText(DamagedActor, DamageType->GetClass(), DamagedActor->GetActorLocation(), DisplayText);
	}
}

void USAttributeComponent::OnTakePointDamage(AActor* DamagedActor, float Damage, AController* InstigatedBy, FVector HitLocation, UPrimitiveComponent* FHitComponent, FName BoneName,
	FVector ShotFromDirection, const UDamageType* DamageType, AActor* DamageCauser)
{
	if (DamagedActor)
	{
		ModifyHealthAttribute(Damage);

		const FText DisplayText = FText::AsNumber(FMath::Abs(Damage));

		USBlueprintLibrary::SpawnFloatingText(DamagedActor, DamageType->GetClass(), HitLocation, DisplayText);
	}
}

void USAttributeComponent::OnTakeRadialDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, FVector Origin, FHitResult HitInfo, AController* InstigatedBy,
	AActor* DamageCauser)
{
	if (DamagedActor)
	{
		ModifyHealthAttribute(Damage);

		const FText DisplayText = FText::AsNumber(FMath::Abs(Damage));

		// Safety check to make sure HitInfo's Actor is valid.
		const FVector TextLocation = HitInfo.GetActor() ? HitInfo.GetActor()->GetActorLocation() : DamagedActor->GetActorLocation();

		USBlueprintLibrary::SpawnFloatingText(DamagedActor, DamageType->GetClass(), TextLocation, DisplayText);
	}
}

bool USAttributeComponent::GetAttributeByTag(FGameplayTag Tag, FAttribute& Attribute) const
{
	for (const TPair<FGameplayTag, FAttribute>& Pair : Attributes)
	{
		if (Pair.Key.MatchesTagExact(Tag))
		{
			Attribute = Attributes[Tag];
			return true;
		}
	}

	return false;
}

void USAttributeComponent::ModifyAttribute(FGameplayTag Tag, float Delta)
{
	if (Tag.MatchesTagExact(DamageTag))
	{
		ModifyHealthAttribute(Delta);
	}
	else
	{
		FAttribute Attribute;
		if (GetAttributeByTag(Tag, Attribute))
		{
			Attribute.ModifyValue(Delta);
			OnAttributeChanged.Broadcast(Attribute);

			Attributes[Tag] = Attribute;
		}
	}
}

void USAttributeComponent::ModifyHealthAttribute(float Delta)
{
	FAttribute Health;
	const FGameplayTag HealthTag = FGameplayTag::RequestGameplayTag(FName("Attribute.Health"));

	FAttribute Armor;
	const FGameplayTag ArmorTag = FGameplayTag::RequestGameplayTag(FName("Attribute.Armor"));

	Delta = FMath::Abs(Delta);

	if (GetAttributeByTag(ArmorTag, Armor))
	{
		const float DamageAfterArmor = Delta - Armor.CurrentValue;

		ModifyAttribute(ArmorTag, -Delta);

		if (GetAttributeByTag(HealthTag, Health))
		{
			if (DamageAfterArmor > 0.f)
			{
				ModifyAttribute(HealthTag, -DamageAfterArmor);
			}
		}
	}
	else
	{
		ModifyAttribute(HealthTag, -Delta);
	}
}
