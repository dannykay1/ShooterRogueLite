// Copyright Danny Kay 2021


#include "Components/SInteractionComponent.h"
#include "Widgets/SInteractionWidgetComponent.h"
#include "DrawDebugHelpers.h"
#include "Player/SCharacter.h"


// Sets default values for this component's properties
USInteractionComponent::USInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	LastInteractionCheckTime = 0.f;
	bInteractHeld = false;

	InteractionCheckFrequency = 0.1f;
	InteractionCheckDistance = 1000.f;
	InteractionCheckRadius = 10.f;
}

// Called when the game starts
void USInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	CharacterOwner = Cast<ASCharacter>(GetOwner());
}

// Called every frame
void USInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetWorld()->TimeSince(LastInteractionCheckTime) > InteractionCheckFrequency)
	{
		PerformInteractionCheck();
	}
}

void USInteractionComponent::PerformInteractionCheck()
{
	if (!CharacterOwner) return;

	LastInteractionCheckTime = GetWorld()->GetTimeSeconds();

	FCollisionObjectQueryParams QueryParams;
	QueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	FVector EyeLocation;
	FRotator EyeRotation;

	CharacterOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	const FVector End = EyeLocation + (EyeRotation.Vector() * InteractionCheckDistance);

	FHitResult Hit;

	FCollisionShape Shape;
	Shape.SetSphere(InteractionCheckRadius);

	const bool bBlockingHit = GetWorld()->SweepSingleByObjectType(Hit, EyeLocation, End, FQuat::Identity, QueryParams, Shape);

	FColor LineColor = FColor::Red;

	if (bBlockingHit && Hit.GetActor())
	{
		if (USInteractionWidgetComponent* Interactable = Cast<USInteractionWidgetComponent>(Hit.GetActor()->GetComponentByClass(USInteractionWidgetComponent::StaticClass())))
		{
			const float Distance = Hit.Distance;
			const float InteractionDistance = Interactable->InteractionDistance;

			if (Interactable != GetInteractable() && Distance <= InteractionDistance)
			{
				FoundNewInteractable(Interactable);
			}
			else if (GetInteractable() && Distance > InteractionDistance)
			{
				CouldntFindInteractable();
			}

			LineColor = FColor::Green;
			//DrawDebugSphere(GetWorld(), Hit.ImpactPoint, InteractionCheckRadius, 32, LineColor, false, 2.f);

			return;
		}
	}

	CouldntFindInteractable();

	//DrawDebugLine(GetWorld(), EyeLocation, End, LineColor, false, 2.f, 0, 2.f);
}

void USInteractionComponent::CouldntFindInteractable()
{
	if (!ensure(CharacterOwner))
	{
		return;
	}

	if (CharacterOwner->GetWorldTimerManager().IsTimerActive(TimerHandle_Interact))
	{
		CharacterOwner->GetWorldTimerManager().ClearTimer(TimerHandle_Interact);
	}

	if (USInteractionWidgetComponent* Interactable = GetInteractable())
	{
		Interactable->EndFocus(CharacterOwner);

		if (bInteractHeld)
		{
			EndInteract();
		}
	}

	ViewedInteractionComponent = nullptr;
}

void USInteractionComponent::FoundNewInteractable(USInteractionWidgetComponent* Interactable)
{
	EndInteract();

	if (USInteractionWidgetComponent* OldInteractable = GetInteractable())
	{
		OldInteractable->EndFocus(CharacterOwner);
	}

	ViewedInteractionComponent = Interactable;
	Interactable->BeginFocus(CharacterOwner);
}

void USInteractionComponent::BeginInteract()
{
	bInteractHeld = true;

	if (USInteractionWidgetComponent* Interactable = GetInteractable())
	{
		Interactable->BeginInteract(CharacterOwner);

		const float InteractionTime = Interactable->InteractionTime;

		if (FMath::IsNearlyZero(InteractionTime))
		{
			Interact();
		}
		else
		{
			CharacterOwner->GetWorldTimerManager().SetTimer(TimerHandle_Interact, this, &USInteractionComponent::Interact, InteractionTime, false);
		}
	}
}

void USInteractionComponent::EndInteract()
{
	if (!ensure(CharacterOwner))
	{
		return;
	}
	
	bInteractHeld = false;

	CharacterOwner->GetWorldTimerManager().ClearTimer(TimerHandle_Interact);

	if (USInteractionWidgetComponent* Interactable = GetInteractable())
	{
		Interactable->EndInteract(CharacterOwner);
	}
}

bool USInteractionComponent::IsInteracting() const
{
	if (!ensure(CharacterOwner))
	{
		return false;
	}
	
	return CharacterOwner->GetWorldTimerManager().IsTimerActive(TimerHandle_Interact);
}

float USInteractionComponent::GetRemainingInteractionTime() const
{
	if (!ensure(CharacterOwner))
	{
		return 0.f;
	}
	
	return IsInteracting()
	       ? CharacterOwner->GetWorldTimerManager().GetTimerRemaining(TimerHandle_Interact)
	       : 0.f;
}

void USInteractionComponent::Interact()
{
	if (!ensure(CharacterOwner))
	{
		return;
	}
	
	CharacterOwner->GetWorldTimerManager().ClearTimer(TimerHandle_Interact);

	if (USInteractionWidgetComponent* Interactable = GetInteractable())
	{
		Interactable->Interact(CharacterOwner);
	}
}
