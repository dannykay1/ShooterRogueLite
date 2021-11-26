// Copyright Danny Kay 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SWeapon.generated.h"

class USkeletalMeshComponent;
class UParticleSystem;
class USoundCue;
class UCameraShakeBase;
class UDamageType;
class USAction;
class ASCharacter;

UCLASS()
class SHOOTERROGUELITE_API ASWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/* Weapon mesh. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	USkeletalMeshComponent* MeshComp;

	UPROPERTY(VisibleDefaultsOnly, Category = Sockets)
	FName MuzzleSocketName;

	UPROPERTY(VisibleDefaultsOnly, Category = Sockets)
	FName SightSocketName;

	UPROPERTY(VisibleDefaultsOnly, Category = Sockets)
	FName LeftHandSocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon)
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Effects)
	TSubclassOf<UCameraShakeBase> CameraShake;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Effects)
	UParticleSystem* MuzzleEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Effects)
	USoundCue* MuzzleSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Actions)
	USAction* FireAction;

public:
	/* Gets the Sight socket on the weapon mesh, used for player 1st person animations. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Sockets)
	FTransform GetSightSocketTransform();

	/* Gets the LeftHand socket on the weapon mesh, used for player 1st person animations. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Sockets)
	FTransform GetLeftHandSocketTransform();

	UFUNCTION(BlueprintCallable, Category = Actions)
	void Equip(ASCharacter* Character);

	UFUNCTION(BlueprintCallable, Category = Actions)
	void UnEquip(ASCharacter* Character);

	/** Adds the weapon's abilities to the owner. */
	UFUNCTION(BlueprintCallable, Category = Abilities)
	void AddAbilities();

	/** Removes the weapon's abilities from the owner. */
	void RemoveAbilities() const;
};
