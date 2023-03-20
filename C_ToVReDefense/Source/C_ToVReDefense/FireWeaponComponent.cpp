// Fill out your copyright notice in the Description page of Project Settings.


#include "FireWeaponComponent.h"

#include "ComponentUtils.h"
#include "Components/SkeletalMeshComponent.h"
#include "HandController.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SceneComponent.h"
#include "Projectile.h"

// Sets default values for this component's properties
UFireWeaponComponent::UFireWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bIsFiring = false;
}



void UFireWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UFireWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UE_LOG(LogTemp, Warning, TEXT("Tick: %f"), TriggerAxisValue);
	if (SkeletalMeshComponent)
	{
		float AnimationTime = TriggerAxisValue * FiringAnimation->SequenceLength;
		SkeletalMeshComponent->SetPlayRate(0.f);
		SkeletalMeshComponent->SetPosition(FMath::Clamp(AnimationTime, 0.f, FiringAnimation->SequenceLength));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("error 3t/7: ProjectileClasses not found"));
	}
}

void UFireWeaponComponent::SetWeapon(USkeletalMeshComponent* NewSkeletalMeshComponent,
                                     FTransform NewMuzzleLocation)
{
	SkeletalMeshComponent = NewSkeletalMeshComponent;
	MuzzleTransform = NewMuzzleLocation;
	if (SkeletalMeshComponent && FiringAnimation)
	{
		SkeletalMeshComponent->SetAnimationMode(EAnimationMode::AnimationSingleNode);
		SkeletalMeshComponent->SetAnimation(FiringAnimation);
		SkeletalMeshComponent->Play(true);
		SkeletalMeshComponent->SetPlayRate(0.f);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("error 3t/7: Skeletal Mesh Component not found"));
	}
	
}
void UFireWeaponComponent::SetWeaponAmmo(TSubclassOf<UParticleSystem> NewMuzzleFlash,
	UAnimSequence* NewFiringAnimation, TSubclassOf<AProjectile> NewProjectileClasses, int32 NewAmmoSize,
	USoundCue* NewFireSound)
{
	MuzzleFlash = NewMuzzleFlash;
	FiringAnimation = NewFiringAnimation;
	ProjectileClasses = NewProjectileClasses;
	AmmoSize = NewAmmoSize;
	FireSound = NewFireSound;
	
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
