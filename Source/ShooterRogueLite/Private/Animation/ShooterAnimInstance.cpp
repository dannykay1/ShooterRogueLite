// Copyright Danny Kay 2021


#include "Animation/ShooterAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"


UShooterAnimInstance::UShooterAnimInstance()
{
	bIsMoving = false;
	bIsTargeting = false;
	Speed = 0.0f;
	Direction = 0.0f;
}

void UShooterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	APawn* PawnOwner = TryGetPawnOwner();
	if (PawnOwner)
	{
		CharacterOwner = Cast<ACharacter>(PawnOwner);
	}
}

void UShooterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!ensure(CharacterOwner)) return;

	FVector Velocity = CharacterOwner->GetVelocity();

	// Zero out z velocity so animation only uses x and y values for speed.
	Velocity.Z = 0.0f;

	Speed = Velocity.Size();

	bIsMoving = Speed > 0.1f;

	if (CharacterOwner->GetCharacterMovement())
	{
		bIsFalling = CharacterOwner->GetCharacterMovement()->IsFalling();
		bIsCrouching = CharacterOwner->GetCharacterMovement()->IsCrouching();
	}

	Direction = CalculateDirection(Velocity, CharacterOwner->GetActorRotation());

	FRotator ControlRotation = CharacterOwner->GetControlRotation();
	FRotator ActorRotation = CharacterOwner->GetActorRotation();

	FRotator CurrentRotation = FRotator(Pitch, 0.0f, 0.0f);
	FRotator TargetRotation = UKismetMathLibrary::ComposeRotators(ControlRotation, ActorRotation);

	FRotator FinalRotator = UKismetMathLibrary::RInterpTo(CurrentRotation, TargetRotation, DeltaSeconds, 15.0f);
	Pitch = UKismetMathLibrary::ClampAngle(FinalRotator.Pitch, -90.0f, 90.0f);
}
