// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CustomCharacterMovementComponent.generated.h"

UENUM(BlueprintType)
namespace ECustomMovementMode
{
	enum Type
	{
		MOVE_Climb UMETA(DisplayName = "Climb Mode")
	};
}
/**
 * 
 */
UCLASS()
class ROPECLIMBING_API UCustomCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

	protected:
	virtual  void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode) override;
	virtual void PhysCustom(float deltaTime, int32 Iterations) override;

	private:

	FHitResult DoCapsuleTraceSingleForObjects(const FVector& Start,const FVector& End,bool bDrawDebugShape, bool bDrawPresistentShapes);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Climbing, meta = (AllowPrivateAccess = "true"))
	float ClimbCapsuleTraceRadius = 50.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Climbing, meta = (AllowPrivateAccess = "true"))
	float ClimbCapsuleTraceHalfHeight = 72.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Climbing, meta = (AllowPrivateAccess = "true"))
	TArray<TEnumAsByte<EObjectTypeQuery>> ClimbableSurfaceTraceTypes;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Climbing, meta = (AllowPrivateAccess = "true"))
	float MaxBreakClimbDeceleration = 400.0f;
	
	UFUNCTION()
	FHitResult TraceClimbableRope();

public :
	void ToogleClimbing(bool bEnableClimb);
	bool IsClimbing() const;
	bool CanStartClimbing();
	void StartClimbing();
	void StopClimbing();
	void PhysClimb(float deltaTime, int32 Iterations);
};
