// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/GameModes/ToonTankGameModeBase.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	// set the health to default value
	Health = DefaultHealth;
	// get current gamemode
	GameModeRef = Cast<AToonTankGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	// bind on take damage method
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
}

void UHealthComponent::TakeDamage(AActor *DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage == 0.f || Health <= 0.f) {
		return ;
	}

	Health = FMath::Clamp(Health - Damage, 0.0f, DefaultHealth);

	UE_LOG(LogTemp, Warning, TEXT("%f health left"), Health)

	if (Health <= 0.f) {
		if (!GameModeRef) {
			UE_LOG(LogTemp, Warning, TEXT("Health component has no game mod ref"));
		} else {
			GameModeRef->ActorDied(GetOwner());
		}
	}
}
