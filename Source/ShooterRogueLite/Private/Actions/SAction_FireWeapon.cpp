// Copyright Danny Kay 2021


#include "Actions/SAction_FireWeapon.h"

#include "Actions/SActionComponent.h"

USAction_FireWeapon::USAction_FireWeapon()
{
	bCanFire = true;
	TimeBetweenShots = 0.5f;
}

void USAction_FireWeapon::Initialize(USActionComponent* NewActionComp)
{
	Super::Initialize(NewActionComp);
}

void USAction_FireWeapon::StopAction(AActor* Instigator)
{
	Super::StopAction(Instigator);

	if (bCanFire)
	{
		bCanFire = false;

		FTimerHandle TimerHandle_FireDelay;
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "StopFire", Instigator);

		GetWorld()->GetTimerManager().SetTimer(TimerHandle_FireDelay, Delegate, TimeBetweenShots, false);
	}
}

bool USAction_FireWeapon::CanActivateAction(AActor* Instigator)
{
	return Super::CanActivateAction(Instigator) && bCanFire;
}

void USAction_FireWeapon::StopFire(AActor* Instigator)
{
	bCanFire = true;
}