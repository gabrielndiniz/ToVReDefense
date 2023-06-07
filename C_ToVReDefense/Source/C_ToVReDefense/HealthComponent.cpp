#include "HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	MaxHealth = 100.f;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	bIsDead = false;
}

void UHealthComponent::TakeDamage(float Damage)
{
	if (bIsDead)
	{
		return;
	}

	float NewHealth = FMath::Clamp(Health - Damage, 0.f, MaxHealth);

	float HealthDelta = NewHealth - Health;

	UpdateHealth(HealthDelta);

	if (Health <= 0.f)
	{
		Die();
	}
}

float UHealthComponent::GetHealth() const
{
	return Health;
}

float UHealthComponent::GetMaxHealth() const
{
	return MaxHealth;
}

FText UHealthComponent::GetHealthPercentage() const
{
	float NumberHealthPercentage = (Health / MaxHealth) * 100.f;
	if (NumberHealthPercentage != 100.f)
	{
		NumberHealthPercentage = FMath::Clamp(NumberHealthPercentage, 1.f, 99.f);
	}
	int32 RoundedPercentage = FMath::RoundToInt(NumberHealthPercentage);

	return FText::Format(FText::FromString("{0}%"), FText::AsNumber(RoundedPercentage));
}

void UHealthComponent::UpdateHealth(float HealthChange)
{
	Health += HealthChange;
	OnHealthChanged.Broadcast(Health, HealthChange);
}

// Handle death
void UHealthComponent::Die()
{
	bIsDead = true;
	
	OnDeath.Broadcast();
}

