// Fill out your copyright notice in the Description page of Project Settings.


#include "FireWeaponComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Projectile.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/KismetMathLibrary.h" 

// Sets default values for this component's properties
UFireWeaponComponent::UFireWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}



void UFireWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->RegisterAllComponents();

	LastComponentForward = GetOwner()->GetActorForwardVector();
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
	return MuzzleSocket->GetComponentTransform();
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
                                            USoundBase* NewFireSound, USceneComponent* NewMuzzleSocket, float NewCallbackTime,
                                            bool bNewIsTurret, UStaticMeshComponent* NewTurret)
{
	MuzzleFlash = NewMuzzleFlash;
	ProjectileClass = NewProjectileClasses;
	FireSound = NewFireSound;


	//if (NewAmmoSize)
	//{
	//	AmmoSize = NewAmmoSize;
	//}

	if (bNewIsTurret && NewTurret != nullptr)
	{
		bIsTurret = true;
		Turret = NewTurret;
		LastComponentForward = Turret->GetForwardVector();
	}

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

	FVector SpawnLocation = GetMuzzleTransform().GetLocation();
	FRotator SpawnRotation = GetMuzzleTransform().GetRotation().Rotator();

	UGameplayStatics::PlaySoundAtLocation(this, FireSound, SpawnLocation);

	// Spawn MuzzleFlash
	if (MuzzleFlash)
	{
		UWorld* const World = GetWorld();
		if (World)
		{
			UGameplayStatics::SpawnEmitterAtLocation(World, MuzzleFlash, SpawnLocation, SpawnRotation, FVector(1), true, EPSCPoolMethod::None, true);
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


void UFireWeaponComponent::PointAtTarget(FVector Target, FVector PointAt, bool IsTargeting)
{
	if (Turret == nullptr)
	{
		return;
	}

	float DistanceToTarget = FVector::Dist(Target, PointAt);

	if (DistanceToTarget < Tolerance && IsTargeting)
	{
		return;
	}

	const FVector ComponentLocation = Turret->GetComponentLocation();
	const FQuat ComponentRotation = Turret->GetComponentQuat();

	const FQuat DesiredRotation = UKismetMathLibrary::FindLookAtRotation(ComponentLocation, Target).Quaternion();

	float CurrentRotationSpeed = RotationSpeed;

	if (DistanceToTarget < Correction)
	{
		float ChangeOnSpeed = (1 - CorrectionFactor) * DistanceToTarget / Correction + CorrectionFactor;

		CurrentRotationSpeed = CurrentRotationSpeed * ChangeOnSpeed;
	}

	const FQuat NewRotation = FQuat::Slerp(ComponentRotation, DesiredRotation, CurrentRotationSpeed);

	// Set the new rotation for the component
	Turret->SetWorldRotation(NewRotation);
}
