// Copyright Danny Kay 2021

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SInteractableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class USInteractableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface implemented in any classes that will work directly with the SInteractionComponent.
 */
class SHOOTERROGUELITE_API ISInteractableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent)
	void Interact(APawn* InstigatorPawn);
};
