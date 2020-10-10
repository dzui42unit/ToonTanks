// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanks/Pawns/TankPawn.h"
#include "ToonTanks/Pawns/TurretPawn.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/PlayerControllers/PlayerControllerBase.h"
#include "ToonTankGameModeBase.h"

void AToonTankGameModeBase::BeginPlay() 
{
    Super::BeginPlay();
    HandleGameStart();
}

void AToonTankGameModeBase::HandleGameStart() 
{  
    TurretsNumber = GetTargetTurretNumber();
    // get a pointer to the player
    Player = Cast<ATankPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
    PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));   
    GameStart();

    if (PlayerControllerRef) {
        PlayerControllerRef->SetPlayerEnabledState(false);
    
        FTimerHandle PlayerEnableHandle;

// GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &ATurretPawn::CheckFireCondition, FireRate, true);

        FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerControllerRef, &APlayerControllerBase::SetPlayerEnabledState, true);
        GetWorld()->GetTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, StartDelay, false);
    }
}

void AToonTankGameModeBase::HandleGameOver(bool PlayerWon) 
{
    GameOver(PlayerWon);
}

void AToonTankGameModeBase::ActorDied(AActor* DeadActor) 
{
    if (DeadActor == Player) {
        Player->HandleDestruction();
        HandleGameOver(false);
        if (PlayerControllerRef) {
            PlayerControllerRef->SetPlayerEnabledState(false);
        }
    } else if (ATurretPawn* TurretDestroyed = Cast<ATurretPawn>(DeadActor)) {
        TurretDestroyed->HandleDestruction();
        TurretsNumber--;
        if (TurretsNumber == 0) {
            HandleGameOver(true);
        }
    }
    // UE_LOG(LogTemp, Warning, TEXT("A Pawn died"));
}

int32 AToonTankGameModeBase::GetTargetTurretNumber() 
{
      // gettting all the rurrets in the level and checking its numbers
    TArray<AActor*>    TurretActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATurretPawn::StaticClass(), TurretActors);  

    return TurretActors.Num();
}
