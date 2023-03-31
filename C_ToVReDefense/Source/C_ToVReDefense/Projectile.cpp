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
	

}

void AProjectile::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{

	
	UE_LOG(LogTemp, Warning, TEXT("Ready to destroy 0"));
	LaunchBlast->Deactivate();
	ImpactBlast->Activate();

//	SetRootComponent(ImpactBlast);
	if (DamageRadius > 0)
	{
		TArray<AActor*> OverlappingActors;
	
		CollisionMesh->GetOverlappingActors(OverlappingActors);

		for (AActor* OverlappingActor : OverlappingActors)
		{
			UHealthComponent* HealthComponent = OverlappingActor->FindComponentByClass<UHealthComponent>();
			if (HealthComponent)
			{
				float DistanceFromImpact = FVector::Distance(OverlappingActor->GetActorLocation(), Hit.ImpactPoint);
				float Damage = ProjectileDamage * FMath::Clamp(1.f - DistanceFromImpact / DamageRadius, 0.f, 1.f);
				HealthComponent->TakeDamage(Damage);
			}
		}
		
		UE_LOG(LogTemp, Warning, TEXT("Ready to destroy "));
	}
	else
	{
		UHealthComponent* HealthComponent = OtherActor->FindComponentByClass<UHealthComponent>();

		if (HealthComponent)

		{

			HealthComponent->TakeDamage(ProjectileDamage);

		}
		
		UE_LOG(LogTemp, Warning, TEXT("Ready to destroy 1"));
	}
	ExplosionForce->Radius = ExplosionIntensity;
	ExplosionForce->FireImpulse();
	
	UE_LOG(LogTemp, Warning, TEXT("Ready to destroy 2"));
	Destroy();
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AProjectile::OnTimerExpire, DestroyDelay, false);
}
// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::SetProjectile(UStaticMeshComponent* NewCollisionMesh,
	UProjectileMovementComponent* NewProjectileMovement, UParticleSystemComponent* NewLaunchBlast,
	UParticleSystemComponent* NewImpactBlast, URadialForceComponent* NewExplosionForce, float NewDestroyDelay,
	float NewProjectileDamage, float NewDamageRadius, float NewSpeed, float newExplosionIntensity)
{
	CollisionMesh = NewCollisionMesh;
	ProjectileMovement = NewProjectileMovement;
	LaunchBlast = NewLaunchBlast;
	ImpactBlast = NewImpactBlast;
	ExplosionForce = NewExplosionForce;
	DestroyDelay = NewDestroyDelay;
	ProjectileDamage = NewProjectileDamage;
	DamageRadius = NewDamageRadius;
	Speed = NewSpeed;
	ExplosionIntensity = newExplosionIntensity;
	

	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
}


void AProjectile::OnTimerExpire()
{
	UE_LOG(LogTemp, Warning, TEXT("Ready to destroy"));
	Destroy();
}
