// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "HealthComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	if (!bIsHeavyRocket)
	{
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AProjectile::OnTimerAfterHit, DestroyDelayOnFire, false);
	}
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AProjectile::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	if (OtherActor == GetOwner())
	{
		UE_LOG(LogTemp, Warning, TEXT("Error 1nD@: OtherActor is equal to the owner!"));
		return;
	}
	CauseDamage(OtherActor, Hit);
}

void AProjectile::SetProjectile(UStaticMeshComponent* NewCollisionMesh,
	UProjectileMovementComponent* NewProjectileMovement, UParticleSystemComponent* NewLaunchBlast,
	UParticleSystemComponent* NewImpactBlast, URadialForceComponent* NewExplosionForce, USoundBase* NewImpactSound,
	float NewDestroyDelay, float NewProjectileDamage, float NewDamageRadius, float NewSpeed, float newExplosionIntensity)
{
	CollisionMesh = NewCollisionMesh;
	ProjectileMovement = NewProjectileMovement;
	LaunchBlast = NewLaunchBlast;
	ImpactBlast = NewImpactBlast;
	ExplosionForce = NewExplosionForce;
	DestroyDelayOnHit = NewDestroyDelay;
	ProjectileDamage = NewProjectileDamage;
	DamageRadius = NewDamageRadius;
	Speed = NewSpeed;
	ExplosionIntensity = newExplosionIntensity;
	ImpactSound = NewImpactSound;
	ImpactBlast->ActivateSystem(false);

	if (bIsHeavyRocket)
	{
		LaunchBlast->ActivateSystem(false);
		ProjectileMovement->SetVelocityInLocalSpace(FVector::ZeroVector);
	}
	else
	{
		ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	}
}


void AProjectile::CauseDamage(AActor* OtherActor, const FHitResult& Hit)
{
	if (!bIsReady)
	{
		return;
	}

	if (LaunchBlast)
	{
		LaunchBlast->ActivateSystem(false);
	}
	if (ImpactBlast)
	{
		ImpactBlast->ActivateSystem(true);
	}
	if (ImpactSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), GetActorRotation(), SoundVolumeMultiplier);
	}
	


	if (DamageRadius > 0)
	{
		TArray<FHitResult> HitResults;
		FVector ExplosionCenter = Hit.ImpactPoint;

		FCollisionQueryParams QueryParams;
		QueryParams.bTraceComplex = true;
		QueryParams.bReturnPhysicalMaterial = false;

		GetWorld()->SweepMultiByChannel(HitResults, ExplosionCenter, ExplosionCenter, FQuat::Identity,
			ECC_Visibility, FCollisionShape::MakeSphere(DamageRadius), QueryParams);

		for (const FHitResult& HitResult : HitResults)
		{
			AActor* OverlappingActor = HitResult.GetActor();
			UHealthComponent* HealthComponent = OverlappingActor->FindComponentByClass<UHealthComponent>();

			if (HealthComponent)
			{
				float DistanceFromImpact = FVector::Distance(OverlappingActor->GetActorLocation(), ExplosionCenter);
				float Damage = ProjectileDamage * FMath::Clamp(1.f - DistanceFromImpact / DamageRadius, 0.f, 1.f);
				HealthComponent->TakeDamage(Damage);
			}
		}		
	}
	else
	{
		UHealthComponent* HealthComponent = OtherActor->FindComponentByClass<UHealthComponent>();

		if (HealthComponent)

		{

			HealthComponent->TakeDamage(ProjectileDamage);


		}
		else
		{
			
			UE_LOG(LogTemp, Warning, TEXT("The ammo does not have a HealthComponent. Name of the actor: %s"), *OtherActor->GetName());
			if (OtherActor->GetParentActor())
			{
				UE_LOG(LogTemp, Warning, TEXT("The ammo does not have a HealthComponent. Name of the parent actor: %s"), *OtherActor->GetParentActor()->GetName());
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("The ammo does not have a HealthComponent and does not have parent."));
			}
				
		}
	}
	ExplosionForce->Radius = ExplosionIntensity;
	ExplosionForce->FireImpulse();
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AProjectile::OnTimerAfterHit, DestroyDelayOnHit, false);
	bIsReady = false;
	
}


void AProjectile::LaunchProjectile() 
{
	LaunchBlast->Activate();
	SetActorEnableCollision(false);
	if (ProjectileMovement)
	{
		ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Error 1nD@: ProjectileMovement not found!"));
		return;
	}

	FTimerHandle CollisionTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AProjectile::OnTimerAfterLaunch,
		EnableCollisionOnLaunch, false);
}


void AProjectile::OnTimerAfterHit()
{
	Destroy();
}

void AProjectile::OnTimerAfterLaunch()
{
	SetActorEnableCollision(true);
}
