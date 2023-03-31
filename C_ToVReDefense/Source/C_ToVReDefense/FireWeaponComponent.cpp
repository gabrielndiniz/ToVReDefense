// Fill out your copyright notice in the Description page of Project Settings.


#include "FireWeaponComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Projectile.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values for this component's properties
UFireWeaponComponent::UFireWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}



void UFireWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->RegisterAllComponents();
}

void UFireWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TriggerAxisValue > 0.9f)
	{
		Fire();
	}
	
}

FTransform UFireWeaponComponent::GetMuzzleTransform() const
{
	const USkeletalMeshComponent* MeshComponent = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
	if (!ensureMsgf(MeshComponent, TEXT("error 3t/7: no SkeletalMeshComponent found on owner!")))
	{
		return FTransform::Identity;
	}
	return MeshComponent->GetSocketTransform(MuzzleSocket);;
}

float UFireWeaponComponent::GetCallbackProgression()
{
	const float ActualTime = GetWorld()->GetRealTimeSeconds();
	if (ActualTime <= StartSliderTime)
	{
		return 0;
	}

	if (ActualTime >= StartSliderTime + CallbackTime)
	{
		bCanFire = true;
		bIsFiring = false;
		return 0;
	}
	const float MidTime = StartSliderTime + CallbackTime / 2.0f;
	if (ActualTime == MidTime)
	{
		return 1.0f;
	}

	const float DeltaTime = FMath::Abs(ActualTime - MidTime);
	const float HalfCallbackTime = CallbackTime / 2.0f;

	const float Progression = 1.0f - (DeltaTime / HalfCallbackTime) * (DeltaTime / HalfCallbackTime);

	return FMath::Clamp(Progression, 0.0f, 1.0f);
}

void UFireWeaponComponent::SetWeaponAndAmmo(UParticleSystem* NewMuzzleFlash, TSubclassOf<AProjectile> NewProjectileClasses, //int32 NewAmmoSize,
                                            USoundBase* NewFireSound,  FName NewMuzzleSocket, float NewCallbackTime)
{
	MuzzleFlash = NewMuzzleFlash;
	ProjectileClass = NewProjectileClasses;
	FireSound = NewFireSound;
	//if (NewAmmoSize)
	//{
	//	AmmoSize = NewAmmoSize;
	//}
	if (CallbackTime)
	{
		CallbackTime = NewCallbackTime;
	}
	MuzzleSocket = NewMuzzleSocket;
			
}


void UFireWeaponComponent::Fire()
{
	GetCallbackProgression();
	if (!bCanFire)
	{
		return;
	}
	else
	{
		StartSliderTime = GetWorld()->GetRealTimeSeconds();
		bCanFire = false;
	}
	
    
	bIsFiring = true;


	// Play FireSound

	FVector SpawnLocation = GetMuzzleTransform().GetLocation();
	FRotator SpawnRotation = GetMuzzleTransform().GetRotation().Rotator();

	
	UGameplayStatics::PlaySoundAtLocation(this, FireSound, SpawnLocation);

	

	// Spawn MuzzleFlash
	if (MuzzleFlash)
	{
		UWorld* const World = GetWorld();
		if (World)
		{
			UGameplayStatics::SpawnEmitterAtLocation(World,MuzzleFlash,SpawnLocation,SpawnRotation,FVector(1),true,EPSCPoolMethod::None,true);
		
		}
	}


	if (ProjectileClass)
	{
		
		AProjectile* ProjectileToFire = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
			if (ProjectileToFire)
			{
				ProjectileToFire->SetOwner(GetOwner());
			}
	}

}
