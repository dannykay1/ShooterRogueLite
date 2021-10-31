// Copyright Danny Kay 2021


#include "Actions/SAttributeComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	HealthAttribute = FAttribute(FGameplayTag::RequestGameplayTag("Attribute.Health"), 100.f);
	ArmorAttribute = FAttribute(FGameplayTag::RequestGameplayTag("Attribute.Armor"), 100.f);
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
	ModifyAttribute(FGameplayTag::RequestGameplayTag("Attribute.Health"), -Damage);
	UE_LOG(LogTemp, Warning, TEXT("Damage %f"), Damage);
}

void USAttributeComponent::HandleRadialDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, FVector Origin, FHitResult HitInfo, AController* InstigatedBy,
                                              AActor* DamageCauser)
{
	ModifyAttribute(FGameplayTag::RequestGameplayTag("Attribute.Health"), -Damage);
}

void USAttributeComponent::ModifyAttribute(FGameplayTag Tag, float Delta)
{
	if (HealthAttribute.MatchesTagExact(Tag))
	{
		OnModifyAttribute(HealthAttribute, Delta);
	}
	else if (ArmorAttribute.MatchesTagExact(Tag))
	{
		OnModifyAttribute(ArmorAttribute, Delta);
	}
}

void USAttributeComponent::OnModifyAttribute(FAttribute& Attribute, float Delta) const
{
	Attribute.ModifyValue(Delta);
	OnAttributeChanged.Broadcast(Attribute, Delta);
}
