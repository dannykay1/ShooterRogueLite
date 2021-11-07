// Copyright Danny Kay 2021

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "SAction.generated.h"

class UWorld;
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

	/* Initializes the ability with the USActionComponent being passed in. */
	void Initialize(USActionComponent* NewActionComp);

	UFUNCTION(BlueprintCallable, Category = Action)
	FORCEINLINE USActionComponent* GetOwningComponent() const { return ActionComp; }

	/* Action tags to start/stop. */
	UPROPERTY(EditDefaultsOnly, Category = Tags)
	FGameplayTag AbilityTag;

	/* Tags added to owning ActionComponent, removed when action stops. */
	UPROPERTY(EditDefaultsOnly, Category = Tags)
	FGameplayTagContainer GrantedTags;

	/* Once activated, any actions with these tags will be cancelled. */
	UPROPERTY(EditDefaultsOnly, Category = Tags)
	FGameplayTagContainer CancelAbilitiesWithTag;

	/** Action can only start if OwningActor has none of these Tags applied */
	UPROPERTY(EditDefaultsOnly, Category = Tags)
	FGameplayTagContainer BlockedTags;

	/* Gets the world from the Actor Owner. */
	virtual UWorld* GetWorld() const override;

	UPROPERTY(EditDefaultsOnly, Category = Action)
	bool bAutoStart;

	UFUNCTION(BlueprintPure, Category = Action)
	FORCEINLINE bool GetIsRunning() const { return bIsRunning; }

	/* Determines if Action can be started. Also calls CheckCost. */
	bool CanActivateAction(AActor* Instigator);

	/* Defaults to true. Can check any cost associated with the Action. */
	UFUNCTION(BlueprintNativeEvent, Category = Action)
	bool CanStart(AActor* Instigator);

	/* Starts the action and calls OnStartAction for blueprint implementation. */
	UFUNCTION(BlueprintCallable, Category = Action)
	virtual void StartAction(AActor* Instigator);

	/* Blueprint event that extends StartAction behavior. */
	UFUNCTION(BlueprintImplementableEvent, Category = Action)
	void OnStartAction(AActor* Instigator);

	/* Stops the action and calls OnStartAction for blueprint implementation. */
	UFUNCTION(BlueprintCallable, Category = Action)
	virtual void StopAction(AActor* Instigator);

	/* Blueprint event that extends StopAction behavior. */
	UFUNCTION(BlueprintImplementableEvent, Category = Action)
	void OnStopAction(AActor* Instigator);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Action)
	USActionComponent* ActionComp;

	/* Flag to ensure Action is not starting/stopping at wrong times. */
	bool bIsRunning;
};
