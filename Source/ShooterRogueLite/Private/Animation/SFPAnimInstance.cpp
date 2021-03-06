// Copyright Danny Kay 2021


#include "Animation/SFPAnimInstance.h"

#include "SBlueprintLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Player/SPlayerCharacter.h"


USFPAnimInstance::USFPAnimInstance()
{
	AimDownSightsTag = FGameplayTag::RequestGameplayTag("Action.Animation.AimDownSights");
	bIsAimingDownSights = false;

	SprintingTag = FGameplayTag::RequestGameplayTag("Action.Sprint");
	bIsSprinting = false;

	bIsMoving = false;
	Speed = 0.0f;

	InterpSpeedLeftHand = 15.f;
	
	InterpSpeedSwayRotation = 5.f;
	
	InterpSpeedRecoil = 10.f;
	
	InterpSpeedFinalRecoil = 15.f;
}

void USFPAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	APawn* PawnOwner = TryGetPawnOwner();
	if (PawnOwner)
	{
		CharacterOwner = Cast<ASPlayerCharacter>(PawnOwner);
	}

	InitializeTransforms();
}

void USFPAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!CharacterOwner) return;

	bIsAimingDownSights = USBlueprintLibrary::ActorHasTag(CharacterOwner, AimDownSightsTag);

	bIsSprinting = USBlueprintLibrary::ActorHasTag(CharacterOwner, SprintingTag);

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

	LeftHandIKTransform = UKismetMathLibrary::TInterpTo(LeftHandIKTransform, CharacterOwner->GetLeftHandTransform(), DeltaSeconds, InterpSpeedLeftHand);
}

void USFPAnimInstance::InitializeTransforms()
{
	FTimerHandle Delay;
	GetWorld()->GetTimerManager().SetTimer(Delay, this, &USFPAnimInstance::InitializeTransforms_Delayed, 0.3f);
}

void USFPAnimInstance::InitializeTransforms_Delayed()
{
	if (CharacterOwner)
	{
		SightTransform = CharacterOwner->GetAimDownSightTransform();
		RelativeHandTransform = CharacterOwner->GetRightHandSocketTransform();
	}
	else if (TryGetPawnOwner())
	{
		SightTransform = RelativeHandTransform = TryGetPawnOwner()->GetActorTransform();
		UE_LOG(LogTemp, Fatal, TEXT("InitializeTransforms_Delayed: CharacerOwner is nullptr!"));
	}
}

void USFPAnimInstance::CalculateRotators(float DeltaSeconds)
{
	const FRotator ControlRotation = CharacterOwner->GetControlRotation();

	const FRotator DeltaRotation = ControlRotation - OldRotation;

	UnmodifiedRotation = UKismetMathLibrary::RInterpTo(UnmodifiedRotation, DeltaRotation, DeltaSeconds, InterpSpeedSwayRotation);

	SwayRotation.Roll = UnmodifiedRotation.Pitch * 3.f;
	SwayRotation.Pitch = 0.f;
	SwayRotation.Yaw = UnmodifiedRotation.Yaw * -1.f;

	OldRotation = ControlRotation;
}

void USFPAnimInstance::CalculateRecoil(float DeltaSeconds)
{
	RecoilTransform = UKismetMathLibrary::TInterpTo(RecoilTransform, FTransform::Identity, DeltaSeconds, InterpSpeedRecoil);
	
	FinalRecoilTransform = UKismetMathLibrary::TInterpTo(FinalRecoilTransform, RecoilTransform, DeltaSeconds, InterpSpeedFinalRecoil);
}

void USFPAnimInstance::SetRecoil(FTransform NewRecoil)
{
	RecoilTransform = NewRecoil;
}
