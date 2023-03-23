// Fill out your copyright notice in the Description page of Project Settings.


#include "FireWeaponComponent.h"

#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"

// Sets default values for this component's properties
UFireWeaponComponent::UFireWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bIsFiring = false;
}



void UFireWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UFireWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TriggerAxisValue > 0.9f)
	{
		Fire();
	}
	
}

void UFireWeaponComponent::SetWeaponAndAmmo(TSubclassOf<UParticleSystem> NewMuzzleFlash, TSubclassOf<AProjectile> NewProjectileClasses, int32 NewAmmoSize,
	USoundCue* NewFireSound, FTransform NewMuzzleLocation, float NewCallbackTime)
{
	MuzzleFlash = NewMuzzleFlash;
	ProjectileClasses = NewProjectileClasses;
	AmmoSize = NewAmmoSize;
	FireSound = NewFireSound;
	CallbackTime = NewCallbackTime;
	MuzzleTransform = NewMuzzleLocation;
	
	if (ProjectileClasses)
	{
		for (int i =0; i<AmmoSize; ++i)
		{
			AProjectile* NewProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClasses, FVector::ZeroVector, FRotator::ZeroRotator);
			Clip.Add(NewProjectile);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("error 3t/7: ProjectileClasses not found"));
	}
	
}


void UFireWeaponComponent::Fire()
{
	if (bIsFiring)
	{
		return;
	}
    
	bIsFiring = true;


}
