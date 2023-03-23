// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabbable.h"

#include "FireWeaponComponent.h"

// Sets default values
AGrabbable::AGrabbable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	GrabbableRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(GrabbableRootComponent);

}

void AGrabbable::BeginPlay()
{
	Super::BeginPlay();

	if (FindComponentByClass<UFireWeaponComponent>() == nullptr)
	{
		return;
	}
	FireComponent = FindComponentByClass<UFireWeaponComponent>();
	if (FireComponent)
	{
		// Set the SkeletalMeshComponent 
		SkeletalMeshComponent = Cast<USkeletalMeshComponent>(GetComponentByClass(USkeletalMeshComponent::StaticClass()));
		if (!SkeletalMeshComponent)
		{
			UE_LOG(LogTemp, Error, TEXT("error z9A@: Skeletal Mesh Component not found"));
		}
	}


}

void AGrabbable::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	
}


void AGrabbable::SetTriggerAxisValue(float Axis) const
{
	if (FireComponent)
	{
		FireComponent->SetTriggerAxisValue(Axis);
	}
}

