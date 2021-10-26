// Copyright Danny Kay 2021

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "SAction.generated.h"

class USActionComponent;

/**
 * 
 */
UCLASS(Blueprintable)
class SHOOTERROGUELITE_API USAction : public UObject
{
	GENERATED_BODY()

public:
	/* Sets default values. */
	USAction();

	void Initialize(USActionComponent* NewActionComp);
	
	/* Action tags to start/stop. */
	UPROPERTY(EditDefaultsOnly, Category = Tags)
	FGameplayTag AbilityTag;

	/* Tags added to owning ActionComponent, removed when action stops. */
	UPROPERTY(EditDefaultsOnly, Category = Tags)
	FGameplayTagContainer GrantedTags;
	
	/* Once activated, any actions with these tags will be cancelled. */
	UPROPERTY(EditDefaultsOnly, Category = Tags)
	FGameplayTagContainer CancelAbilitiesWithTag;
	
	/* Actions with these tags will be blocked while this action is active. */
	UPROPERTY(EditDefaultsOnly, Category = Tags)
	FGameplayTagContainer BlockAbilitiesWithTag;

	UFUNCTION(BlueprintCallable, Category = Action)
	USActionComponent* GetOwningComponent() const;

	/* Starts the action and calls OnStartAction for blueprint implementation. */
	void StartAction(AActor* Instigator);

	/* Blueprint event that extends StartAction behavior. */
	UFUNCTION(BlueprintImplementableEvent, Category = Action)
	void OnStartAction(AActor* Instigator);
	
	/* Stops the action and calls OnStartAction for blueprint implementation. */
	void StopAction(AActor* Instigator);

	/* Blueprint event that extends StopAction behavior. */
	UFUNCTION(BlueprintImplementableEvent, Category = Action)
	void OnStopAction(AActor* Instigator);

protected:
	USActionComponent* ActionComp;
};
