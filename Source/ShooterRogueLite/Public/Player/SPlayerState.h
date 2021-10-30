// Copyright Danny Kay 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnCreditsChanged, class ASPlayerState*, PlayerState, int32, NewCredits, int32, Delta);

UCLASS()
class SHOOTERROGUELITE_API ASPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASPlayerState();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	/* In game currency. Given when killing enemies, can be spent. */
	UPROPERTY(EditDefaultsOnly, Category = Credits)
	int32 Credits;

public:
	UFUNCTION(BlueprintPure, Category = Credits)
	FORCEINLINE int32 GetCredits() const { return Credits; }

	UFUNCTION(BlueprintPure, Category = Credits)
	bool HasEnoughCredits(int32 Delta) const;

	UFUNCTION(BlueprintCallable, Category = Credits)
	void AddCredits(int32 Delta);

	UFUNCTION(BlueprintCallable, Category = Credits)
	bool RemoveCredits(int32 Delta);

	UPROPERTY(BlueprintAssignable, Category = Credits)
	FOnCreditsChanged OnCreditsChanged;
};
