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




protected:

	virtual void BeginPlay() override;

public:

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	

public:

	
	UFUNCTION()
	void SetTriggerAxisValue(float NewTriggerAxisValue) {TriggerAxisValue = NewTriggerAxisValue; }
	
	UFUNCTION(BlueprintPure, Category = "Firing")
	float GetTriggerAxisValue() const {return TriggerAxisValue;}

	UFUNCTION(BlueprintPure, Category="MyCategory")
	FTransform GetMuzzleTransform() const{return MuzzleTransform;}



	UFUNCTION(BlueprintPure, Category="MyCategory")
	float GetCallbackTime() const	{return CallbackTime;}

//need to take out USkeletalMeshComponent and stuff
	UFUNCTION(BlueprintCallable, Category = "Firing")
	void SetWeaponAndAmmo(TSubclassOf<UParticleSystem> NewMuzzleFlash, TSubclassOf<class AProjectile> NewProjectileClasses, int32 NewAmmoSize,
	class USoundCue* NewFireSound, FTransform NewMuzzleLocation, float NewCallbackTime);
	
private:
	
	UPROPERTY()
	float FiringRate;

	UPROPERTY()
	float DamagePerShot;
	
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
		
	bool bIsFiring;

	int32 CurrentProjectileIndex;

	float LastFireTime;


};
