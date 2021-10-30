// Copyright Danny Kay 2021

#pragma once

#include "CoreMinimal.h"
#include "SAction.h"
#include "SActionEffect.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERROGUELITE_API USActionEffect : public USAction
{
	GENERATED_BODY()

public:
	/* Sets default values. */
	USActionEffect();

	virtual void StartAction(AActor* Instigator) override;

	virtual void StopAction(AActor* Instigator) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Effect)
	float Duration;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Effect)
	float Period;

	FTimerHandle TimerHandle_Duration;
	FTimerHandle TimerHandle_Period;

	UFUNCTION(BlueprintCallable, Category = Effect)
	void ExecutePeriodicEffect(AActor* Instigator);

	/* Blueprint event that extends ExecutePeriodicEffect. */
	UFUNCTION(BlueprintImplementableEvent, Category = Action)
	void OnExecutePeriodicEffect(AActor* Instigator);
};
