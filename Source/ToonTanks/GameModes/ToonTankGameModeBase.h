// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTankGameModeBase.generated.h"

/**
 * 
 */

class ATankPawn;
class ATurretPawn;
class APlayerControllerBase;

UCLASS()
class TOONTANKS_API AToonTankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:

	ATankPawn*	Player;
	int32 		TurretsNumber = 0;

	APlayerControllerBase*	PlayerControllerRef;

	int32  	GetTargetTurretNumber();
	void	HandleGameStart();
	void	HandleGameOver(bool PlayerWon);

public:
	void	ActorDied(AActor* DeadActor);

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game Loop")
	int32	StartDelay = 3;

	virtual void 	BeginPlay();
	UFUNCTION(BlueprintImplementableEvent)
	void			GameStart();
	UFUNCTION(BlueprintImplementableEvent)
	void			GameOver(bool PlayerWon);
};
