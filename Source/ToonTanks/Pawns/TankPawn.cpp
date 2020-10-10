// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraComponent.h"
#include "Engine/World.h"
#include "TankPawn.h"

ATankPawn::ATankPawn()
{
    TankSpringComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm Spring "));
    TankSpringComp->SetupAttachment(RootComponent);

    TankCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Tank Camera"));
    TankCamera->SetupAttachment(TankSpringComp);
}

// Called when the game starts or when spawned
void ATankPawn::BeginPlay()
{
	Super::BeginPlay();

    bIsPlayerAlive = true;

    // getting our player controller and store it
    // PlayerControllers are used by human players to control Pawns.
    PlayerControllerRef = Cast<APlayerController>(GetController());
}

void ATankPawn::HandleDestruction() 
{
    Super::HandleDestruction();

    bIsPlayerAlive = false;

    // hide the actor on the scene and stop its tick functionality
    // save performance
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);

    // Destroy();
}

bool ATankPawn::GetIsPlayerAlive() const
{
   return bIsPlayerAlive;
}

// Called every frame
void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    Rotate();
    Move();

    if (PlayerControllerRef) {
        FHitResult TraceHitResult;
        PlayerControllerRef->GetHitResultUnderCursor(ECC_Visibility, false, TraceHitResult);
        FVector HitLocation = TraceHitResult.ImpactPoint;
        RotateTurret(HitLocation); 
    }
}

// Called to bind functionality to input
void ATankPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis("MoveForward", this, &ATankPawn::CalculateMoveInput);
    PlayerInputComponent->BindAxis("Turn", this, &ATankPawn::CalculateRotationInput);
    PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ATankPawn::Fire);
}

void ATankPawn::CalculateMoveInput(float Value) 
{
    // multiply by DeltatimeSeconds to make it framerate independent
    MoveDirection = FVector(Value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0, 0);   
}

void ATankPawn::CalculateRotationInput(float Value) 
{
    // multiply by DeltatimeSeconds to make it framerate independent
    float RotateAmount = Value * RotateSpeed * GetWorld()->DeltaTimeSeconds;
    FRotator Rotation = FRotator(0, RotateAmount, 0);
    RotationDirection = FQuat(Rotation);
}

void ATankPawn::Move() 
{
    AddActorLocalOffset(MoveDirection);
}

void ATankPawn::Rotate() 
{
    AddActorLocalRotation(RotationDirection);
}
