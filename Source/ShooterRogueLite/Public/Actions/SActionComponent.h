// Copyright Danny Kay 2021

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "SActionComponent.generated.h"

class USAction;

/**
* 
*/
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SHOOTERROGUELITE_API USActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USActionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY()
	TArray<USAction*> Actions;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/* Returns true if ActiveGameplayTags matches any of the incoming tags. */
	UFUNCTION(BlueprintPure, Category = Tags)
	bool HasActiveTag(FGameplayTagContainer Tags) const;
	
	/* Gameplay tags on this component. Added when Action starts, removed when Action ends. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tags)
	FGameplayTagContainer ActiveGameplayTags;

	UFUNCTION(BlueprintCallable, Category = Action)
	void AddAction(TSubclassOf<USAction> ActionClass);
	
	UFUNCTION(BlueprintCallable, Category = Action)
	bool StartAction(AActor* Instigator, FGameplayTag ActionTag);
	
	UFUNCTION(BlueprintCallable, Category = Action)
	bool StopAction(AActor* Instigator, FGameplayTag ActionTag);
};
