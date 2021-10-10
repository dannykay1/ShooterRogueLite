﻿// Copyright Danny Kay 2021


#include "Player/SCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/SInteractionComponent.h"
#include "Components/SkeletalMeshComponent.h"


// Sets default values
ASCharacter::ASCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComponent->bUsePawnControlRotation = true;
	CameraComponent->SetupAttachment(GetMesh());
	CameraComponent->SetRelativeLocation(FVector(-30.f, 0.f, -80.f));

	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh1P"));
	Mesh1P->SetupAttachment(CameraComponent);
	Mesh1P->SetRelativeLocation(FVector(0.f, 0.f, -130.f));
	Mesh1P->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	InteractionComponent = CreateDefaultSubobject<USInteractionComponent>(TEXT("InteractionComponent"));
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &ACharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &ACharacter::AddControllerYawInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);	
}

void ASCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void ASCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}