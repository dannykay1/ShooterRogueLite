// Copyright Danny Kay 2021


#include "Animation/SFPAnimInstance.h"
#include "Actions/SActionComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Player/SCharacter.h"


USFPAnimInstance::USFPAnimInstance()
{
	SprintingTag = FGameplayTag::RequestGameplayTag("Action.Sprint");
	bIsSprinting = false;
	
	bIsMoving = false;
	Speed = 0.0f;
}

void USFPAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	APawn* PawnOwner = TryGetPawnOwner();
	if (PawnOwner)
	{
		CharacterOwner = Cast<ASCharacter>(PawnOwner);
	}

	InitializeTransforms();
}

void USFPAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!CharacterOwner) return;

	if (CharacterOwner->GetActionComponent())
	{
		bIsSprinting = CharacterOwner->GetActionComponent()->ActiveGameplayTags.HasTag(SprintingTag);
	}

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

	CalculateRotators(DeltaSeconds);
	CalculateRecoil(DeltaSeconds);

	LeftHandIKTransform = GetLeftHandIKTransform();
}

void USFPAnimInstance::InitializeTransforms()
{
	FTimerHandle Delay;
	GetWorld()->GetTimerManager().SetTimer(Delay, this, &USFPAnimInstance::InitializeTransforms_Delayed, 0.3f);
}

void USFPAnimInstance::InitializeTransforms_Delayed()
{
	SightTransform = GetSightTransform();
	RelativeHandTransform = GetRelativeHandTransform();
}

void USFPAnimInstance::CalculateRotators(float DeltaSeconds)
{
	FRotator ControlRotation = CharacterOwner->GetControlRotation();

	FRotator DeltaRotation = ControlRotation - OldRotation;

	UnmodifiedRotation = UKismetMathLibrary::RInterpTo(UnmodifiedRotation, DeltaRotation, DeltaSeconds, 5.f);

	SwayRotation.Roll = UnmodifiedRotation.Pitch * 3.f;
	SwayRotation.Pitch = 0.f;
	SwayRotation.Yaw = UnmodifiedRotation.Yaw * -1.f;

	OldRotation = ControlRotation;
}

void USFPAnimInstance::CalculateRecoil(float DeltaSeconds)
{
	RecoilTransform = UKismetMathLibrary::TInterpTo(RecoilTransform, FTransform::Identity, DeltaSeconds, 10.f);

	FinalRecoilTransform = UKismetMathLibrary::TInterpTo(FinalRecoilTransform, RecoilTransform, DeltaSeconds, 15.f);
}

void USFPAnimInstance::SetRecoil(FTransform NewRecoil)
{
	RecoilTransform = NewRecoil;
}
