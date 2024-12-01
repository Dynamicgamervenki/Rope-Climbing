// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CustomCharacterMovementComponent.h"

#include <DebugHelpers.h>

#include "Kismet/KismetSystemLibrary.h"

void UCustomCharacterMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

FHitResult UCustomCharacterMovementComponent::DoCapsuleTraceSingleForObjects(const FVector& Start, const FVector& End,
                                                                             bool bDrawDebugShape,bool bDrawPresistentShapes)
{
	EDrawDebugTrace::Type DebugTrace = EDrawDebugTrace::None;
	FHitResult CapsuleTraceHitResult;

	if (bDrawDebugShape)
	{
		DebugTrace = EDrawDebugTrace::ForOneFrame;
		if (bDrawPresistentShapes)
		{
			DebugTrace = EDrawDebugTrace::Persistent;
		}
	}
	
	UKismetSystemLibrary::CapsuleTraceSingleForObjects
	(
		this,
		Start,
		End,
		ClimbCapsuleTraceRadius,
		ClimbCapsuleTraceHalfHeight,
		ClimbableSurfaceTraceTypes,
		false,
		TArray<AActor*>(),
		DebugTrace,
		CapsuleTraceHitResult,
		false
	);

	return CapsuleTraceHitResult;
}

FHitResult UCustomCharacterMovementComponent::TraceClimbableRope()
{
	const FVector StartOffset = UpdatedComponent->GetForwardVector() * 30.f;
	const FVector Start = UpdatedComponent->GetComponentLocation() + StartOffset;
	const FVector End = Start + UpdatedComponent->GetForwardVector();
	
	return  DoCapsuleTraceSingleForObjects(Start,End,true,true);
}

void UCustomCharacterMovementComponent::ToogleClimbing(bool bEnableClimb)
{
	if (bEnableClimb)
	{
		if (CanStartClimbing())
		{
			//Start Climbing
			Debug::Print(TEXT("Can Start Climbing"),FColor::Green,3);
		}
		else
		{
			Debug::Print(TEXT("Cannot Start Climbing"),FColor::Red,3);
		}
	}
	else
	{
		//Stop Climbing
	}
}

bool UCustomCharacterMovementComponent::IsClimbing() const
{
	return MovementMode == MOVE_Custom && CustomMovementMode == MOVE_Custom;
}

bool UCustomCharacterMovementComponent::CanStartClimbing()
{
	if (IsFalling()) return false;
	if (!TraceClimbableRope().bBlockingHit) return false;

	return true;
}
