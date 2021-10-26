// Copyright Danny Kay 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SItemChest.generated.h"

class UStaticMeshComponent;

UCLASS()
class SHOOTERROGUELITE_API ASItemChest : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASItemChest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Components)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Components)
	UStaticMeshComponent* LidMesh;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Components)
	UStaticMeshComponent* TreasureMesh;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float TargetPitch;
};
