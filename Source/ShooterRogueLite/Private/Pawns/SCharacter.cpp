// Copyright Danny Kay 2021


#include "Pawns/SCharacter.h"
#include "Abilities/SAbilitySystemComponent.h"
#include "Abilities/SAttributeSet.h"


// Sets default values
ASCharacter::ASCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<USAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<USAttributeSet>(TEXT("AttributeSet"));
}

void ASCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	
    AbilitySystemComponent->GiveStartingAbilities();
    AbilitySystemComponent->GiveDefaultAttribute();
	
	AbilitySystemComponent->BindASCInput(InputComponent);
}

UAbilitySystemComponent* ASCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	AbilitySystemComponent->BindASCInput(PlayerInputComponent);
}

