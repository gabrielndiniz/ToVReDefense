#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, Health, float, HealthDelta);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class C_TOVREDEFENSE_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	// Called when the game starts
	virtual void BeginPlay() override;

	// Take damage and update health
	UFUNCTION(BlueprintCallable, Category = "Health")
	void TakeDamage(float Damage);

	// Get current health
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealth() const;

	// Get max health
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetMaxHealth() const;

	// Health variable
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health")
	float MaxHealth;

protected:
	// Current health
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Health")
	float Health;

	// Death event dispatcher
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnDeath OnDeath;

	// Health change event dispatcher
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnHealthChanged OnHealthChanged;

	// Update health event
	UFUNCTION(BlueprintCallable, Category = "Health")
	void UpdateHealth(float HealthChange);

	// Flag to prevent taking damage while dead
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Health")
	bool bIsDead;

private:
	// Handle death
	void Die();
	void OnDeath_Implementation();
};
