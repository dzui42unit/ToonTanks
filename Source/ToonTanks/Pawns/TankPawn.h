// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "TankPawn.generated.h"

class UCameraComponent;
class USpringArmComponent;

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATankPawn : public ABasePawn
{
	GENERATED_BODY()

private:
	// camera component of the tank
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* TankCamera;
	// This component tries to maintain its children at a fixed distance from the parent,
	// but will retract the children if there is a collision, and spring back when there is no collision.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent*	TankSpringComp;
	APlayerController*		PlayerControllerRef;

	FVector					MoveDirection;
	FQuat					RotationDirection;


	void					CalculateMoveInput(float Value);
	void					CalculateRotationInput(float Value);
	void					Move();
	void					Rotate();

	UPROPERTY(EditAnywhere, BlueprintReadOnly , Category = "Tank Movement", meta = (AllowPrivateAccess = "true"))
	float					MoveSpeed = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly , Category = "Tank Movement", meta = (AllowPrivateAccess = "true"))
	float					RotateSpeed = 100.f;

	bool					bIsPlayerAlive;

public:
	// Sets default values for this pawn's properties
	ATankPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void HandleDestruction() override;

	bool 		 GetIsPlayerAlive() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
