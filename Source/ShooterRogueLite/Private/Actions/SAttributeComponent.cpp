// Copyright Danny Kay 2021


#include "Actions/SAttributeComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	HealthAttribute = FAttribute();
	HealthAttribute.Tag = FGameplayTag::RequestGameplayTag("Attribute.Health");
	HealthAttribute.Initialize(100.f);

	ArmorAttribute = FAttribute();
	ArmorAttribute.Initialize(100.f);
}

// Called when the game starts
void USAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

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
	ModifyAttribute(HealthAttribute, -Damage);
}

void USAttributeComponent::HandleRadialDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, FVector Origin, FHitResult HitInfo, AController* InstigatedBy,
	AActor* DamageCauser)
{
	ModifyAttribute(HealthAttribute, -Damage);
}

void USAttributeComponent::ModifyAttribute(FAttribute& Attribute, float Delta)
{
	Attribute.ModifyValue(Delta);
	OnAttributeChanged.Broadcast(Attribute, Delta);
}
