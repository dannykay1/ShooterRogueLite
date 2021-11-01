// Copyright Danny Kay 2021

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "SAttributeComponent.generated.h"

USTRUCT(BlueprintType)
struct SHOOTERROGUELITE_API FAttribute
{
	GENERATED_BODY()

	FAttribute()
	{
		CurrentValue = BaseValue = 0.f;
	}

	FAttribute(FGameplayTag DefaultTag, float DefaultValue)
	{
		Tag = DefaultTag;
		CurrentValue = BaseValue = DefaultValue;
	}

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag Tag;

	UPROPERTY(BlueprintReadOnly)
	float CurrentValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float BaseValue;

	bool MatchesTagExact(FGameplayTag TagToCompare) const
	{
		return Tag.MatchesTagExact(TagToCompare);
	}	

	void ModifyValue(float Delta)
	{
		CurrentValue = FMath::Clamp(CurrentValue + Delta, 0.f, BaseValue);
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAttributeChanged, FAttribute, Attribute, FVector, HitLocation, float, Delta);

/**
* Handles any attributes, defined by FGameplayTag.
*/
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SHOOTERROGUELITE_API USAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USAttributeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void HandlePointDamage(AActor* DamagedActor, float Damage, class AController* InstigatedBy, FVector HitLocation, class UPrimitiveComponent* FHitComponent, FName BoneName,
	                       FVector ShotFromDirection, const class UDamageType* DamageType, AActor* DamageCauser);

	UFUNCTION()
	void HandleRadialDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, FVector Origin, FHitResult HitInfo, class AController* InstigatedBy,
	                        AActor* DamageCauser);

	TMap<FGameplayTag, FAttribute> Attributes;

	UPROPERTY(EditDefaultsOnly, Category = Attributes)
	TMap<FGameplayTag, FAttribute> DefaultAttributes;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Attributes)
	FAttribute Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Attributes)
	FAttribute Armor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Attributes)
	FAttribute Speed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Attributes)
	FAttribute Credits;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Attributes)
	FAttribute Experience;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Attributes)
	FAttribute AmmoAssaultRifle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Attributes)
	FAttribute AmmoShotgun;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Attributes)
	FAttribute AmmoPistol;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Attributes)
	FAttribute AmmoGrenadeLauncher;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Attributes)
	FAttribute AmmoRockerLauncher;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Attributes)
	FAttribute AmmoSniperRifle;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintPure, Category = Attributes)
	FORCEINLINE FAttribute GetHealthAttribute() const { return Health; }
	
	UFUNCTION(BlueprintPure, Category = Attributes)
	FORCEINLINE FAttribute GetArmorAttribute() const { return Armor; }

	UFUNCTION(BlueprintCallable, Category = Attributes)
	void ModifyAttribute(FGameplayTag Tag, FVector HitLocation, float Delta);

	UPROPERTY(BlueprintAssignable, Category = Attribute)
	FOnAttributeChanged OnAttributeChanged;
};
