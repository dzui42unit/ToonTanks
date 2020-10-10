// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "UObject/WeakObjectPtr.h"
#include "Camera/CameraShake.h"
#include "ProjectileBase.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BaseProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile mesh"));
	RootComponent = BaseProjectileMesh;

	BaseProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile movement"));
	BaseProjectileMovement->InitialSpeed = MovementSpeed;
	BaseProjectileMovement->MaxSpeed = MovementSpeed;

	ProjectileTrailParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Projectile trail particles"));
	ProjectileTrailParticles->SetupAttachment(RootComponent);

	InitialLifeSpan = 3.f;
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	BaseProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHitMe);

	UGameplayStatics::SpawnSoundAtLocation(this, LaunchSound, GetActorLocation());

}

void AProjectileBase::OnHitMe(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	// Try to get a reference to the owning class.
	AActor* MyOwner = GetOwner();
	// If for some reason we can't get a valid reference, return as we need to check against the owner. 
	if(!MyOwner)
	{
		return;
	}
	// If the other ISN'T self OR Owner AND exists, then apply damage. 
	if(OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		// aply damage to the actor
		// OtherActor - actor to get damage
		// Damage - amount of damage
		// GetInstigatorController() - Controller that was responsible for causing this damage (e.g. player who shot the weapon)
		// this - Actor that actually caused the damage
		// DamageType - Class that describes the damage that was done.		
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwner->GetInstigatorController(), this, DamageType);
		// Play a bunch of effects here
		UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation());
		// play sound
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
		// make camera shake
		GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(HitShake);
		Destroy();
	}
}