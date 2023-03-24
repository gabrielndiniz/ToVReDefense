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

	UFUNCTION(BlueprintPure, Category="Fire Weapon")
	FTransform GetMuzzleTransform() const{return MuzzleTransform;}

	UFUNCTION(BlueprintPure, Category="Fire Weapon")
	bool GetIsFiring() const	{return bIsFiring;}

	UFUNCTION(BlueprintPure, Category="Fire Weapon")
	float GetCallbackTime() const	{return CallbackTime;}
	
	UFUNCTION(BlueprintCallable, Category="Fire Weapon")
	void SetStartSliderTime(float InitialTime) {StartSliderTime = InitialTime;}
	
	UFUNCTION(BlueprintPure, Category="Fire Weapon")
	float GetCallbackProgression();
	
	UFUNCTION(BlueprintCallable, Category = "Fire Weapon")
	void SetCanFire(bool bNewCanFire) {bCanFire = bNewCanFire;}

	UFUNCTION(BlueprintPure, Category = "Fire Weapon")
	bool GetCanFire() const {return bCanFire;}


//need to take out USkeletalMeshComponent and stuff
	UFUNCTION(BlueprintCallable, Category = "Firing")
	void SetWeaponAndAmmo(TSubclassOf<UParticleSystem> NewMuzzleFlash, TSubclassOf<class AProjectile> NewProjectileClasses, int32 NewAmmoSize,
	class USoundCue* NewFireSound, FTransform NewMuzzleLocation, float NewCallbackTime);
	
	
	void Fire();

	
private:
	
	UPROPERTY()
	float FiringRate;

	UPROPERTY()
	float DamagePerShot;
	
	UPROPERTY()
	float StartSliderTime = -90000000;
	
	UPROPERTY()
	TSubclassOf<class UParticleSystem> MuzzleFlash;


	UPROPERTY()
	TSubclassOf<class AProjectile> ProjectileClasses;

	UPROPERTY()
	int32 AmmoSize;
	
	UPROPERTY()
	class USoundCue* FireSound;
	
	UPROPERTY()
	TArray<class AProjectile*> Clip;
		
	UPROPERTY()
	FTransform MuzzleTransform;

	UPROPERTY()
	float TriggerAxisValue = 0;

	UPROPERTY()
	float CallbackTime = 0;
		
	bool bIsFiring = false;

	bool bCanFire=true;

	int32 CurrentProjectileIndex;

	float LastFireTime;


};
