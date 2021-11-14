// Copyright Danny Kay 2021

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "SActionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTagAdded, FGameplayTag, AddedTag);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTagRemoved, FGameplayTag, RemovedTag);

class USAction;

/**
* Handles activating and deactivating Actions.
* Uses a lock-and-key system.
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

	/* TArray of all Actions currently running. */
	UPROPERTY()
	TArray<USAction*> Actions;

	/* Actions the component will start with. */
	UPROPERTY(EditDefaultsOnly, Category = Action)
	TArray<TSubclassOf<USAction>> DefaultActions;

	/** Bindable event called when action is added. */
	UPROPERTY(BlueprintAssignable)
	FOnTagAdded OnTagAdded;

	/** Bindable event called when action is removed. */
	UPROPERTY(BlueprintAssignable)
	FOnTagRemoved OnTagRemoved;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	/* Gameplay tags on this component. Added when Action starts, removed when Action ends. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tags)
	FGameplayTagContainer ActiveGameplayTags;

	UFUNCTION(BlueprintCallable, Category = Action)
	void AddAction(AActor* Instigator, TSubclassOf<USAction> ActionClass);

	UFUNCTION(BlueprintCallable, Category = Action)
	void RemoveAction(USAction* ActionToRemove);
	
	UFUNCTION(BlueprintCallable, Category = Action)
	bool StartAction(AActor* Instigator, FGameplayTag ActionTag);
	
	UFUNCTION(BlueprintCallable, Category = Action)
	bool StopAction(AActor* Instigator, FGameplayTag ActionTag);

	void CancelAbilitiesWithTags(AActor* Instigator, FGameplayTagContainer Tags);
};
