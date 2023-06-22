// Fill out your copyright notice in the Description page of Project Settings.


#include "FireWeaponComponent.h"

#include "DrawDebugHelpers.h"
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

	//Only for Player. AI will manage Fire at Blueprint.

	if (TriggerAxisValue > 0.9f)
	{
		bIsFiring = true;
	}
	if (!bCanFire)
	{
		GetCallbackProgression();
	}	
	else if (bIsFiring)
	{
		Fire(GetMuzzleTransform().GetLocation(), GetMuzzleTransform().GetRotation().Rotator(), FireSound, MuzzleFlash, ProjectileClass);
	}
}

FTransform UFireWeaponComponent::GetMuzzleTransform() const
{
	if (MuzzleSocket)
	{
		return MuzzleSocket->GetComponentTransform();
	}
	else
	{
		return MuzzleTransform;
	}
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
                                            bool bNewIsTurret, UStaticMeshComponent* NewTurret, bool bNewIsHeavyRocket)
{
	MuzzleFlash = NewMuzzleFlash;
	ProjectileClass = NewProjectileClasses;
	FireSound = NewFireSound;
	bIsHeavyRocket = bNewIsHeavyRocket;


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


void UFireWeaponComponent::Fire(FVector MuzzleLocation, FRotator MuzzleRotation, USoundBase* FireSFX,
							UParticleSystem* FireVFX, TSubclassOf<AProjectile> Projectile)
{
	StartSliderTime = GetWorld()->GetRealTimeSeconds();

	bCanFire = false;


	if (FireSFX)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSFX, MuzzleLocation, MuzzleRotation, SoundVolumeMultiplier);
	}

	if (FireVFX)
	{
		UWorld* const World = GetWorld();
		if (World)
		{
			UGameplayStatics::SpawnEmitterAtLocation(World, FireVFX, MuzzleLocation, MuzzleRotation, FVector(1),
				true, EPSCPoolMethod::None, true);
		}
	}

	if (Projectile && !bIsHeavyRocket)
	{
		AProjectile* ProjectileToFire = GetWorld()->SpawnActor<AProjectile>(Projectile, MuzzleLocation, MuzzleRotation);
		if (ProjectileToFire)
		{
			ProjectileToFire->SetOwner(GetOwner());
		}
	}
	else if (Projectile && bIsHeavyRocket)
	{
		if (AttachedProjectiles.Num()<=0)
		{
			GetOwner()->GetAttachedActors(AttachedProjectiles);
		}
		if (AttachedProjectiles.Num()<=0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Error @3f$: Attached Actors not found!"));
			return;
		}
		AProjectile* AttachedProjectile = Cast<AProjectile>(AttachedProjectiles[0]);
		AttachedProjectiles.RemoveAt(0);
		if (AttachedProjectile)
		{
			AttachedProjectile->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
			AttachedProjectile->LaunchProjectile();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Error @3f$: Attached Actor is not a Projectile type!"));
		}
	}
	AmmoSpent = AmmoSpent+1;
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

bool UFireWeaponComponent::PredictClearShot(const FVector& TargetLocation, const FVector& TargetVelocity,
			float ProjectileSpeed, float MaxPredictionTime, TArray<AActor*> AcceptableTargets) const
{
	FVector StartLocation = GetMuzzleTransform().GetLocation();
	FVector Direction = TargetLocation - StartLocation;
	float Distance = Direction.Size();
	Direction.Normalize();

	float TimeToReachTarget = Distance / ProjectileSpeed;

	FVector PredictedTargetLocation = TargetLocation + TargetVelocity * TimeToReachTarget;

	FVector Error = PredictedTargetLocation - TargetLocation;

	float MaxError = MaxPredictionTime * TargetVelocity.Size();

	if (Error.SizeSquared() <= MaxError * MaxError)
	{
		FHitResult HitResult;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(GetOwner());
		for (auto AcceptableTarget : AcceptableTargets)
		{
			Params.AddIgnoredActor(AcceptableTarget);
		}
		DrawDebugLine(GetWorld(), StartLocation, PredictedTargetLocation, FColor::Green, false, 2.0f, 0, 1.0f);

		bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, PredictedTargetLocation, ECC_Visibility, Params);

		if (bHit)
		{
			//put UE_LOG to know target
			return false;
		}

		return true;
	}
	
	return true;
}