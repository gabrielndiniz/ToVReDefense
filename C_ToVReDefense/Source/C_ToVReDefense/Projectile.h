// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class C_TOVREDEFENSE_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Config")
	void SetProjectile(UStaticMeshComponent* NewCollisionMesh, class UProjectileMovementComponent* NewProjectileMovement, 
						UParticleSystemComponent* NewLaunchBlast, UParticleSystemComponent* NewImpactBlast, 
						class URadialForceComponent* NewExplosionForce, float NewDestroyDelay, float NewProjectileDamage,
						float NewDamageRadius, float NewSpeed, float newExplosionIntensity);

	//if I do not use spawn projectile
	//void LaunchProjectile(FTransform InitialLocation);

	
private:
//	UPROPERTY(EditDefaultsOnly, Category = "Setup")
//	EProjectileType ProjectileType;

	
	UPROPERTY()
	class UProjectileMovementComponent* ProjectileMovement = nullptr;

	UPROPERTY()
	UStaticMeshComponent* CollisionMesh = nullptr;

	UPROPERTY()
	UParticleSystemComponent* LaunchBlast = nullptr;

	UPROPERTY()
	UParticleSystemComponent* ImpactBlast = nullptr;


	UPROPERTY()
	class URadialForceComponent* ExplosionForce = nullptr;

	UPROPERTY()
	float DestroyDelayOnHit = 5.f;
	
	UPROPERTY()
	float DestroyDelayOnFire = 50.f;

	UPROPERTY()
	float ProjectileDamage = 20.f;

	UPROPERTY()
	float DamageRadius = 0.0f;

	UPROPERTY()
	float Speed = 5000.0f;
	
	UPROPERTY()
	float ExplosionIntensity = 100.0f;
	
	UPROPERTY()
	bool bIsReady = true;

	//UPROPERTY()
	//FTransform StartingPoint = FTransform::Identity;
	
	UFUNCTION()
	void OnTimerExpire();

	UPROPERTY()
	FTimerHandle TimerHandle;

};
