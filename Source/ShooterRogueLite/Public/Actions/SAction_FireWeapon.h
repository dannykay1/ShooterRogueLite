// Copyright Danny Kay 2021

#pragma once

#include "CoreMinimal.h"
#include "SAction.h"
#include "SAction_FireWeapon.generated.h"

/**
 * Base class for shooting the player's weapon.
 */
UCLASS()
class SHOOTERROGUELITE_API USAction_FireWeapon : public USAction
{
	GENERATED_BODY()

public:
	/* Sets default values. */
	USAction_FireWeapon();

	virtual void Initialize(USActionComponent* NewActionComp) override;

	virtual void StopAction(AActor* Instigator) override;

	virtual bool CanActivateAction(AActor* Instigator) override;

protected:
	UFUNCTION()
	void StopFire(AActor* Instigator);

	bool bCanFire;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon)
	float TimeBetweenShots;
};
