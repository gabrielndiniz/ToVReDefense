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

protected:

	virtual void BeginPlay() override;

public:

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	

public:

	
	UFUNCTION()
	void SetTriggerAxisValue(float NewTriggerAxisValue) {TriggerAxisValue = NewTriggerAxisValue; }
	
	UFUNCTION(BlueprintPure, Category = "Fire Weapon")
	float GetTriggerAxisValue() const {return TriggerAxisValue;}

	UFUNCTION(BlueprintCallable, Category="Fire Weapon")
	void SetMuzzleTransform(FTransform NewMuzzleTransform) {MuzzleTransform = NewMuzzleTransform;}

	UFUNCTION(BlueprintPure, Category="Fire Weapon")
	FTransform GetMuzzleTransform() const;

	UFUNCTION(BlueprintCallable, Category="Fire Weapon")
	void SetIsFiring(bool bNewIsFiring) {bIsFiring = bNewIsFiring;}

	UFUNCTION(BlueprintPure, Category="Fire Weapon")
	bool GetIsFiring() const	{return bIsFiring;}

	UFUNCTION(BlueprintPure, Category="Fire Weapon")
	float GetCallbackTime() const	{return CallbackTime;}
		
	UFUNCTION(BlueprintPure, Category="Fire Weapon")
	float GetCallbackProgression();
	
	UFUNCTION(BlueprintPure, Category = "Fire Weapon")
	bool GetCanFire() const {return bCanFire;}


//need to take out USkeletalMeshComponent and stuff
	UFUNCTION(BlueprintCallable, Category = "Firing")
	void SetWeaponAndAmmo(UParticleSystem* NewMuzzleFlash, TSubclassOf<class AProjectile> NewProjectileClasses, //int32 NewAmmoSize,
	class USoundBase* NewFireSound, USceneComponent* NewMuzzleSocket, float NewCallbackTime, bool bNewIsTurret,
	UStaticMeshComponent* NewTurret, bool bNewIsHeavyRocket);
	
	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire(FVector MuzzleLocation, FRotator MuzzleRotation, USoundBase* FireSFX, UParticleSystem* FireVFX,
	TSubclassOf<AProjectile> Projectile);

	
	
	UFUNCTION(BlueprintPure, Category = "Firing")
	int32 GetAmmoSpent() const {return AmmoSpent;}

	
	UFUNCTION(BlueprintCallable, Category = "Fire Weapon")
	void PointAtTarget(FVector Target, FVector PointAt, bool IsTargeting);

	
	UFUNCTION(BlueprintPure, Category = "Firing")
	bool PredictClearShot(const FVector& TargetLocation, const FVector& TargetVelocity, float ProjectileSpeed,
	                      float MaxPredictionTime) const;


private:
	
	UPROPERTY()
	float FiringRate;

	UPROPERTY()
	float DamagePerShot;
	
	UPROPERTY()
	float StartSliderTime = -90000000;
	
	UPROPERTY()
	UParticleSystem* MuzzleFlash;


	UPROPERTY()
	TSubclassOf<class AProjectile> ProjectileClass;

	
	UPROPERTY()
	bool bIsTurret = false;

	
	UPROPERTY()
	UStaticMeshComponent* Turret;

	UPROPERTY(EditAnywhere)
	float RotationSpeed = 0.05;

	
	UPROPERTY(EditAnywhere)
	float Tolerance = 1;
	
	UPROPERTY(EditAnywhere)
	float Correction = 100;
	
	UPROPERTY(EditAnywhere)
	float CorrectionFactor = 10;
	//UPROPERTY()
	//int32 AmmoSize = 1;
	
	UPROPERTY()
	class USoundBase* FireSound;

	
	UPROPERTY(EditAnywhere)
	float SoundVolumeMultiplier = 0.1;
	
	UPROPERTY(EditAnywhere)
	bool bIsHeavyRocket = false;
			
	UPROPERTY()
	USceneComponent* MuzzleSocket;

	UPROPERTY()
	float TriggerAxisValue = 0;

	UPROPERTY()
	float CallbackTime = SMALL_NUMBER;
		
	UPROPERTY()
	bool bIsFiring = false;

	UPROPERTY()
	bool bCanFire=true;
	
	UPROPERTY()
	FTransform MuzzleTransform = FTransform::Identity;

	UPROPERTY()
	int32 CurrentProjectileIndex;

	UPROPERTY()
	float LastFireTime;

	UPROPERTY()
	FVector LastComponentForward;

	UPROPERTY()
	TArray<AActor*> AttachedProjectiles;

	UPROPERTY()
	int32 AmmoSpent = 0;

};
