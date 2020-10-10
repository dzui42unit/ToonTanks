// Fill out your copyright notice in the Description page of Project Settings.


#include "Kismet/GameplayStatics.h"
#include "TankPawn.h"
#include "TurretPawn.h"

ATurretPawn::ATurretPawn()
{

}

// Called when the game starts or when spawned
void ATurretPawn::BeginPlay()
{
	Super::BeginPlay();
	// get the time manager, returs FTimeManager that allows to globally manage timers
    // and we create a ne wtimer
    GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &ATurretPawn::CheckFireCondition, FireRate, true);
    // initialize pointer to the player
    PlayerPawn = Cast<ATankPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
    bIsPTurretAlive = true;
}

void ATurretPawn::HandleDestruction() 
{
    Super::HandleDestruction();
    bIsPTurretAlive = false;
}

// Called every frame
void ATurretPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (PlayerPawn && CalculateDistanceToPlayer() <= FireDistance && bIsPTurretAlive) {
        RotateTurret(PlayerPawn->GetActorLocation());
    }
}

void ATurretPawn::CheckFireCondition() 
{
    if (!PlayerPawn || !PlayerPawn->GetIsPlayerAlive() || !bIsPTurretAlive) {
        return ;
    }

    // Returns the player pawn at the specified player index
    if (CalculateDistanceToPlayer() <= FireDistance) {
        Fire();
    }
}

float ATurretPawn::CalculateDistanceToPlayer() 
{
    if (!PlayerPawn) {
        return 0.f;
    }
    // calculate the distance
    return FVector::Distance(this->GetActorLocation(), PlayerPawn->GetActorLocation());
}
