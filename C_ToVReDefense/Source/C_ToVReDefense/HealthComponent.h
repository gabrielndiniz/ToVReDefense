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
	UHealthComponent();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Health")
	void TakeDamage(float Damage);

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealth() const;

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetMaxHealth() const;

	UFUNCTION(BlueprintPure, Category = "Health")
	FText GetHealthPercentage() const;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health")
	float MaxHealth;

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Health")
	float Health;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnDeath OnDeath;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnHealthChanged OnHealthChanged;

	UFUNCTION(BlueprintCallable, Category = "Health")
	void UpdateHealth(float HealthChange);

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Health")
	bool bIsDead;

private:
	void Die();
	void OnDeath_Implementation();
};
