// Copyright Danny Kay 2021

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "STypes.h"
#include "Components/ActorComponent.h"
#include "SAttributeComponent.generated.h"

class UDataTable;

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
	void InitializeAttributes();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION()
	void OnTakePointDamage(AActor* DamagedActor, float Damage, class AController* InstigatedBy, FVector HitLocation, class UPrimitiveComponent* FHitComponent, FName BoneName,
	                       FVector ShotFromDirection, const class UDamageType* DamageType, AActor* DamageCauser);

	UFUNCTION()
	void OnTakeRadialDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, FVector Origin, FHitResult HitInfo, class AController* InstigatedBy,
	                        AActor* DamageCauser);


	UPROPERTY(EditDefaultsOnly, Category = Attribute)
	UDataTable* AttributeTable;

	UPROPERTY(VisibleDefaultsOnly, Category = Attribute)
	FGameplayTag DamageTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attribute)
	TMap<FGameplayTag, FAttribute> Attributes;

public:
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChanged OnAttributeChanged;

	UFUNCTION(BlueprintCallable, Category = Attribute)
	bool GetAttributeByTag(FGameplayTag Tag, FAttribute& Attribute) const;

	UFUNCTION(BlueprintCallable, Category = Attribute)
	void ModifyAttribute(FGameplayTag Tag, float Delta);

	UFUNCTION(BlueprintCallable, Category = Attribute)
	void ModifyHealthAttribute(float Delta);
};
