// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "TurretPawn.generated.h"

class ATankPawn;

UCLASS()
class TOONTANKS_API ATurretPawn : public ABasePawn
{
	GENERATED_BODY()
	
private:
	// check if the fire condition is satisfied
	void 	CheckFireCondition();
	// timer for fire rate
	FTimerHandle	FireRateTimerHandle;
	// fire rate
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float			FireRate = 2.f;
	// distance to trigger fire
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float			FireDistance = 300.f;
	// pointer to the player
	ATankPawn*		PlayerPawn;
	// calculate the distance to the player
	float			CalculateDistanceToPlayer();

	bool					bIsPTurretAlive;

public:
	// Sets default values for this pawn's properties
	ATurretPawn();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void HandleDestruction() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
