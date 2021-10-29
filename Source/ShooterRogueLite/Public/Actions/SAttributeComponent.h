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

	UPROPERTY(BlueprintReadOnly)
	float CurrentValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float BaseValue;

	void Initialize()
	{
		CurrentValue = BaseValue;
	}

	void ModifyValue(float Delta)
	{
		CurrentValue = FMath::Clamp(CurrentValue + Delta, 0.f, BaseValue);
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAttributeChanged, FGameplayTag, Tag, FAttribute, Attribute);

/**
* 
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Attributes)
	TMap<FGameplayTag, FAttribute> Attributes;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = Attributes)
	bool ModifyAttribute(FGameplayTag Tag, float Delta, FAttribute& Attribute);

	UPROPERTY(BlueprintAssignable, Category = Attribute)
	FOnAttributeChanged OnAttributeChanged;
};
