// Copyright Danny Kay 2021


#include "Weapons/SWeapon.h"
#include "Components/SkeletalMeshComponent.h"


// Sets default values
ASWeapon::ASWeapon()
{
	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(MeshComp);
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->CastShadow = false;

	MuzzleSocketName = "Muzzle";
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

void ASWeapon::Equip(ASCharacter* Character)
{
}

void ASWeapon::UnEquip(ASCharacter* Character)
{
}

void ASWeapon::AddAbilities()
{
	AActor* MyOwner = GetOwner();
	if (!ensure(MyOwner))
		return;
}

void ASWeapon::RemoveAbilities() const
{
	AActor* MyOwner = GetOwner();
	if (!ensure(MyOwner))
		return;
}
