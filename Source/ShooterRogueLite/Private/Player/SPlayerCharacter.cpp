﻿// Copyright Danny Kay 2021


#include "Player/SPlayerCharacter.h"
#include "Actions/SActionComponent.h"
#include "Actions/SAttributeComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SInteractionComponent.h"
#include "Components/SkeletalMeshComponent.h"


// Sets default values
ASPlayerCharacter::ASPlayerCharacter()
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

	ActionComponent = CreateDefaultSubobject<USActionComponent>(TEXT("ActionComponent"));
	AttributeComponent = CreateDefaultSubobject<USAttributeComponent>(TEXT("AttributeComponent"));
}

void ASPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

// Called when the game starts or when spawned
void ASPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void ASPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASPlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &ACharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &ACharacter::AddControllerYawInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ASPlayerCharacter::BeginInteract);
	PlayerInputComponent->BindAction("Interact", IE_Released, this, &ASPlayerCharacter::EndInteract);
}

void ASPlayerCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void ASPlayerCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void ASPlayerCharacter::BeginInteract()
{
	InteractionComponent->BeginInteract();
}

void ASPlayerCharacter::EndInteract()
{
	InteractionComponent->EndInteract();
}
