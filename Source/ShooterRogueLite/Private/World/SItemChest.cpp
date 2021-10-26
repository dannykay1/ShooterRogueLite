// Copyright Danny Kay 2021


#include "World/SItemChest.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ASItemChest::ASItemChest()
{
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidMesh"));
	LidMesh->SetupAttachment(BaseMesh);
	LidMesh->SetRelativeLocation(FVector(-35.f, 0.f, 50.f));

	TreasureMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TreasureMesh"));
	TreasureMesh->SetupAttachment(BaseMesh);
	TreasureMesh->SetRelativeLocation(FVector(0.f, 0.f, 50.f));

	TargetPitch = 110.f;
}

// Called when the game starts or when spawned
void ASItemChest::BeginPlay()
{
	Super::BeginPlay();
}