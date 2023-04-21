// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPawn.h"

#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AEnemyPawn::AEnemyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyPawn::OnDeath(UParticleSystem* DeathAnim)
{
	if (GetController())
	{
		GetController()->UnPossess();
	}
	TArray<UPrimitiveComponent*> Components;
	GetComponents<UPrimitiveComponent>(Components);
	for (auto Component : Components)
	{
		if (USkeletalMeshComponent* SkeletalMesh = Cast<USkeletalMeshComponent>(Component))
		{
			SkeletalMesh->SetSimulatePhysics(true);
			SkeletalMesh->BreakConstraint(FVector::ZeroVector, FVector::ZeroVector,"");
			SkeletalMesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		}
		else if (UStaticMeshComponent* StaticMesh = Cast<UStaticMeshComponent>(Component))
		{
			StaticMesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		}
	}

	if (DeathAnim)
	{
		UWorld* const World = GetWorld();
		if (World)
		{
			UGameplayStatics::SpawnEmitterAtLocation(World,DeathAnim,GetActorLocation(),GetActorRotation(),FVector(1),true,EPSCPoolMethod::None,true);
		
		}
	}
}
