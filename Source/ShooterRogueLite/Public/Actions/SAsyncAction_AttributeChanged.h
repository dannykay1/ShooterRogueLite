// Copyright Danny Kay 2021

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Attributes/SAttributeComponent.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "SAsyncAction_AttributeChanged.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAttributeChangedd, FAttribute, Attribute, float, CurrentValue, float, BaseValue);

/**
 * Blueprint node to automatically register a listener for an attribute in AttributeComponent.
 * Very useful in UI.
 */
UCLASS(BlueprintType, meta=(ExposedAsyncProxy = AsyncTask))
class SHOOTERROGUELITE_API USAsyncAction_AttributeChanged : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedd OnAttributeChanged;

	UFUNCTION(BlueprintCallable)
	static USAsyncAction_AttributeChanged* ListenForAttributeChange(USAttributeComponent* AttributeComponent, FGameplayTag Tag);

	UFUNCTION(BlueprintCallable)
	void EndTask();

protected:
	UPROPERTY()
	USAttributeComponent* AttributeComponent;

	FGameplayTag TagToListenFor;

	UFUNCTION()
	void AttributeChanged(const FAttribute Attribute);
};
