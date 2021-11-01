// Copyright Danny Kay 2021


#include "Attributes/SAttributeComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	Health = FAttribute(FGameplayTag::RequestGameplayTag("Attribute.Health"), 100.f);
	Armor = FAttribute(FGameplayTag::RequestGameplayTag("Attribute.Armor"), 100.f);
}

// Called when the game starts
void USAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	for (auto& Attribute : DefaultAttributes)
	{
		Attributes.Add(Attribute.Key, FAttribute(Attribute.Key, Attribute.Value.BaseValue));
	}

	if (AActor* MyOwner = GetOwner())
	{
		MyOwner->OnTakePointDamage.AddDynamic(this, &USAttributeComponent::HandlePointDamage);
		MyOwner->OnTakeRadialDamage.AddDynamic(this, &USAttributeComponent::HandleRadialDamage);
	}
}

// Called every frame
void USAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USAttributeComponent::HandlePointDamage(AActor* DamagedActor, float Damage, AController* InstigatedBy, FVector HitLocation, UPrimitiveComponent* FHitComponent, FName BoneName,
                                             FVector ShotFromDirection, const UDamageType* DamageType, AActor* DamageCauser)
{
	ModifyAttribute(FGameplayTag::RequestGameplayTag("Attribute.Health"), HitLocation, -Damage);
}

void USAttributeComponent::HandleRadialDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, FVector Origin, FHitResult HitInfo, AController* InstigatedBy,
                                              AActor* DamageCauser)
{	
	ModifyAttribute(FGameplayTag::RequestGameplayTag("Attribute.Health"), HitInfo.ImpactPoint, -Damage);
}

void USAttributeComponent::ModifyAttribute(FGameplayTag Tag, FVector HitLocation, float Delta)
{
	for (auto& Attribute : Attributes)
	{
		if (Attribute.Key.MatchesTagExact(Tag))
		{
			Attribute.Value.ModifyValue(Delta);

			const float AbsDelta = FMath::Abs(Delta);
			OnAttributeChanged.Broadcast(Attribute.Value, HitLocation, AbsDelta);
		}
	}
}