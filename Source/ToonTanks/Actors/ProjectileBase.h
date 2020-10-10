// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/PrimitiveComponent.h"
#include "ProjectileBase.generated.h"

class UProjectileMovementComponent;
class UParticleSystem;
class USoundBase;
class UCameraShake;

UCLASS()
class TOONTANKS_API AProjectileBase : public AActor
{
	GENERATED_BODY()

private:
	// COMPONENTS
	// ProjectileMovementComponent updates the position of another component during its tick.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent*	BaseProjectileMovement;
	// mesh of the actor
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent*			BaseProjectileMesh;
	// TSubclassOf is a template class that provides UClass type safety.
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TSubclassOf<UDamageType>		DamageType;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent*	ProjectileTrailParticles;

	// VARIABLES
	// Movement speed
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	float							MovementSpeed = 1000.f;
	// Damage number
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage", meta = (AllowPrivateAccess = "true"))
	float							Damage = 50.f;
	// particle effects
	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem*	HitParticles;

	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase*			LaunchSound;
	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase*			HitSound;

	UPROPERTY(EditAnywhere, Category = "Effects")
	TSubclassOf<UCameraShake>	HitShake;

public:	
	// Sets default values for this actor's properties
	AProjectileBase();

	UFUNCTION()
	void	OnHitMe(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
