// Copyright Danny Kay 2021


#include "DamageTypes/SDamageType.h"
#include "DamageTypes/SFloatingText.h"
#include "UObject/ConstructorHelpers.h"


USDamageType::USDamageType()
{
	Color = FLinearColor::White;

	static ConstructorHelpers::FClassFinder<ASFloatingText> DamageText(TEXT("/Game/Blueprints/BP_DamageText"));
	FloatingTextClass = DamageText.Class;
}
