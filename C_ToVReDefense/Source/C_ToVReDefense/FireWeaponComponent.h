#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FireWeaponComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class C_TOVREDEFENSE_API UFireWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFireWeaponComponent();

	//This will only fire if trigger axis is bigger than 0.9
	void Fire();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Firing")
	float FiringRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Firing")
	float DamagePerShot;


protected:

	virtual void BeginPlay() override;

public:

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	

public:
	
	UFUNCTION()
	void SetWeapon(USkeletalMeshComponent* NewSkeletalMeshComponent, FTransform NewMuzzleLocation);

	
	UFUNCTION()
	void SetTriggerAxisValue(float NewTriggerAxisValue) {TriggerAxisValue = NewTriggerAxisValue;}
	
	UFUNCTION(BlueprintPure, Category = "Firing")
	float GetTriggerAxisValue() const {return TriggerAxisValue;}

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void SetWeaponAmmo(TSubclassOf<class UParticleSystem> NewMuzzleFlash, class UAnimSequence* NewFiringAnimation,
		TSubclassOf<class AProjectile> NewProjectileClasses, int32 NewAmmoSize, class USoundCue* NewFireSound);
	
private:

	UPROPERTY()
	TSubclassOf<class UParticleSystem> MuzzleFlash;

	UPROPERTY()
	class UAnimSequence* FiringAnimation;

	UPROPERTY()
	TSubclassOf<class AProjectile> ProjectileClasses;

	UPROPERTY()
	int32 AmmoSize;
	
	UPROPERTY()
	class USoundCue* FireSound;
	
	UPROPERTY()
	TArray<class AProjectile*> Clip;
	
	UPROPERTY()
	USkeletalMeshComponent* SkeletalMeshComponent;
	
	UPROPERTY()
	FTransform MuzzleTransform;

	UPROPERTY()
	float TriggerAxisValue;
	
	bool bIsFiring;

	int32 CurrentProjectileIndex;

	float LastFireTime;


};
