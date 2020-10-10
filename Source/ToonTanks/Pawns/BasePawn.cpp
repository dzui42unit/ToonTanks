// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "ToonTanks/Actors/ProjectileBase.h"
#include "ToonTanks/Components/HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "Camera/CameraShake.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// create a capsule component and set it as a root
	PawnCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Pawn Capsule colider"));
	RootComponent = PawnCapsule;

	PawnBaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pawn Base Mesh"));
	PawnBaseMesh->SetupAttachment(RootComponent);

	PawnTurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pawn Turret Mesh"));
	PawnTurretMesh->SetupAttachment(PawnBaseMesh);

	PawnProjectile = CreateDefaultSubobject<USceneComponent>(TEXT("Pawn Projectile"));
	PawnProjectile->SetupAttachment(PawnTurretMesh);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health component"));
}

void ABasePawn::RotateTurret(FVector TargetLookAt) 
{
	// create a new vector of the target we are looking at, taking into account only its X, Y position
	FVector TargetLookAtClean = FVector(TargetLookAt.X, TargetLookAt.Y, PawnTurretMesh->GetComponentLocation().Z);
	// start poisition vector
	FVector StartPosition = PawnTurretMesh->GetComponentLocation();
	// calculate the rotation between two actors
	FRotator TurretRotation = FVector(TargetLookAtClean - StartPosition).Rotation();
	// set the rotation for the turret
	PawnTurretMesh->SetWorldRotation(TurretRotation);
}

void ABasePawn::Fire() 
{
	// if we have projectile class set up -> spawn an projectile
	if (ProjectileClass) {
		FVector SpawnStartLocation = PawnProjectile->GetComponentLocation();
		FRotator SpawnStartRotation = PawnProjectile->GetComponentRotation();
		AActor*	TmpPtojectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, SpawnStartLocation, SpawnStartRotation);
		TmpPtojectile->SetOwner(this);
	}	
}

void ABasePawn::HandleDestruction() 
{
	// spawn particles
	UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticles, GetActorLocation());
	// spawn sound
	UGameplayStatics::SpawnSoundAtLocation(this, DestroySound, GetActorLocation());
	// make camera shake
	GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(DeathShake);
}

