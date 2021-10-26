// Copyright Danny Kay 2021


#include "Weapons/SWeapon.h"
#include "Abilities/SAbilitySystemComponent.h"
#include "Abilities/SGameplayAbility.h"
#include "Components/SInteractionWidgetComponent.h"
#include "Components/SkeletalMeshComponent.h"


// Sets default values
ASWeapon::ASWeapon()
{
	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(MeshComp);
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->CastShadow = false;

	InteractionWidgetComp = CreateDefaultSubobject<USInteractionWidgetComponent>(TEXT("InteractionWidgetComp"));

	SightSocketName = "Sight";
	LeftHandSocketName = "LeftHand";
}

// Called when the game starts or when spawned
void ASWeapon::BeginPlay()
{
	Super::BeginPlay();
}

FTransform ASWeapon::GetSightSocketTransform()
{
	return MeshComp
		? MeshComp->GetSocketTransform(SightSocketName)
		: GetActorTransform();
}

FTransform ASWeapon::GetLeftHandSocketTransform()
{
	return MeshComp
		? MeshComp->GetSocketTransform(LeftHandSocketName)
		: GetActorTransform();
}

void ASWeapon::AddAbilities()
{
	AActor* MyOwner = GetOwner();
	if (!ensure(MyOwner))
		return;

	USAbilitySystemComponent* ASC = Cast<USAbilitySystemComponent>(MyOwner->GetComponentByClass(USAbilitySystemComponent::StaticClass()));
	if (!ensure(ASC))
		return;

	for (TSubclassOf<USGameplayAbility> Ability : AbilitiesToGive)
	{
		if (Ability)
		{
			FGameplayAbilitySpecHandle Handle = ASC->GiveAbility(FGameplayAbilitySpec(Ability, 1, static_cast<int32>(Ability.GetDefaultObject()->InputID), this));
			AbilitySpecHandles.Add(Handle);
		}
	}
}

void ASWeapon::RemoveAbilities()
{
	AActor* MyOwner = GetOwner();
	if (!ensure(MyOwner))
		return;

	USAbilitySystemComponent* ASC = Cast<USAbilitySystemComponent>(MyOwner->GetComponentByClass(USAbilitySystemComponent::StaticClass()));
	if (!ensure(ASC))
		return;

	for (FGameplayAbilitySpecHandle& Handle : AbilitySpecHandles)
	{
		ASC->ClearAbility(Handle);
	}
}
