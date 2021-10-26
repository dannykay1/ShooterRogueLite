// Copyright Danny Kay 2021


#include "Weapons/SWeapon.h"
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
}

void ASWeapon::RemoveAbilities()
{
	AActor* MyOwner = GetOwner();
	if (!ensure(MyOwner))
		return;
}
