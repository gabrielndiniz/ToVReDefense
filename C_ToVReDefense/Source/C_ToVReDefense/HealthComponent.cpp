#include "HealthComponent.h"

#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set default max health
	MaxHealth = 100.f;
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// Set initial health
	Health = MaxHealth;

	// Initialize bIsDead flag to false
	bIsDead = false;
}

// Take damage and update health
void UHealthComponent::TakeDamage(float Damage)
{
	// If already dead, don't take any damage
	if (bIsDead)
	{
		return;
	}

	// Calculate new health value
	float NewHealth = FMath::Clamp(Health - Damage, 0.f, MaxHealth);

	// Calculate health change
	float HealthDelta = NewHealth - Health;

	// Update health and dispatch event
	UpdateHealth(HealthDelta);

	// If health is zero or less, die
	if (Health <= 0.f)
	{
		Die();
	}
}

// Get current health
float UHealthComponent::GetHealth() const
{
	return Health;
}

// Get max health
float UHealthComponent::GetMaxHealth() const
{
	return MaxHealth;
}

// Update health and dispatch event
void UHealthComponent::UpdateHealth(float HealthChange)
{
	Health += HealthChange;
	OnHealthChanged.Broadcast(Health, HealthChange);
}

// Handle death
void UHealthComponent::Die()
{
	bIsDead = true;
	if (DeathVFX)
	{
		// Spawn the VFX at the component's location
		UGameplayStatics::SpawnEmitterAtLocation(GetOwner(), DeathVFX, GetOwner()->GetActorLocation());
	}

	if (DeathSFX)
	{
		// Play the SFX
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), DeathSFX, GetOwner()->GetActorLocation());
	}
	
	OnDeath.Broadcast();
}

