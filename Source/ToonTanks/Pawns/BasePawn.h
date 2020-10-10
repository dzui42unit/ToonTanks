// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Particles/ParticleSystem.h"
#include "BasePawn.generated.h"

class UCapsuleComponent;
class AProjectileBase;
class UHealthComponent;
class USoundBase;
class UCameraShake;

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

private:
	// COMPOENENTS
	// creating a capsule component as our collider component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent*		PawnCapsule;
	// static meshes for the model parts of the pawn
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent*	PawnBaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category =  "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent*	PawnTurretMesh;
	// to be able to track its position in the world
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category =  "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent*		PawnProjectile;
	// VARIABLES
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile type", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AProjectileBase>	ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem*	DeathParticles;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile type", meta = (AllowPrivateAccess = "true"))
	UHealthComponent*	HealthComponent;

	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase*			DestroySound;

	UPROPERTY(EditAnywhere, Category = "Effects")
	TSubclassOf<UCameraShake>	DeathShake;	

public:
	// Sets default values for this pawn's properties
	ABasePawn();
	virtual void	HandleDestruction();
	
protected:
	void			RotateTurret(FVector TargetLookAt);
	void			Fire();
};
