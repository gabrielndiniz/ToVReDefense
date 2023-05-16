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
	FTransform GetMuzzleTransform() const;

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
	void SetWeaponAndAmmo(UParticleSystem* NewMuzzleFlash, TSubclassOf<class AProjectile> NewProjectileClasses, //int32 NewAmmoSize,
	class USoundBase* NewFireSound, USceneComponent* NewMuzzleSocket, float NewCallbackTime, bool bNewIsTurret, UStaticMeshComponent* NewTurret);
	
	UFUNCTION()
	void Fire();

	
	UFUNCTION(BlueprintCallable, Category = "Fire Weapon")
	void PointAtTarget(FVector Target, FVector PointAt, bool IsTargeting);

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
	float RotationSpeed = 0;

	
	UPROPERTY(EditAnywhere)
	float Tolerance = 1;
	
	UPROPERTY(EditAnywhere)
	float Correction = 0;
	
	UPROPERTY(EditAnywhere)
	float CorrectionFactor = 1;
	//UPROPERTY()
	//int32 AmmoSize = 1;
	
	UPROPERTY()
	class USoundBase* FireSound;
			
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
	int32 CurrentProjectileIndex;

	UPROPERTY()
	float LastFireTime;

	UPROPERTY()
	FVector LastComponentForward;

};
