// Copyright Danny Kay 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayAbilitySpec.h"
#include "SWeapon.generated.h"

class USkeletalMeshComponent;
class USInteractionWidgetComponent;
class USGameplayAbility;

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

	/* Allows for player interaction, such as picking up this weapon. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	USInteractionWidgetComponent* InteractionWidgetComp;

	UPROPERTY(VisibleDefaultsOnly, Category = Sockets)
	FName SightSocketName;

	UPROPERTY(VisibleDefaultsOnly, Category = Sockets)
	FName LeftHandSocketName;

	/* Abilities to give to owning AbilitySystemComponent. */
	UPROPERTY(EditDefaultsOnly, Category = Abilities)
	TArray<TSubclassOf<USGameplayAbility>> AbilitiesToGive;

	/** Used to remove abilities from owner once unequipped */
	UPROPERTY(BlueprintReadOnly, Category = Abilities)
	TArray<FGameplayAbilitySpecHandle> AbilitySpecHandles;

public:
	/* Gets the Sight socket on the weapon mesh, used for player 1st person animations. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Sockets)
	FTransform GetSightSocketTransform();

	/* Gets the LeftHand socket on the weapon mesh, used for player 1st person animations. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Sockets)
	FTransform GetLeftHandSocketTransform();

	/** Adds the weapon's abilities to the owner. */
	UFUNCTION(BlueprintCallable, Category = Abilities)
	void AddAbilities();

	/** Removes the weapon's abilities from the owner. */
	void RemoveAbilities();
};
