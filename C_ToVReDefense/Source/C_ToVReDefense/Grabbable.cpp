// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabbable.h"

#include "FireWeaponComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

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

	
}

void AGrabbable::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}


void AGrabbable::SetTriggerAxisValue(float Axis) 
{
	TriggerAxisValue = Axis;
	if (FireComponent)
	{
		FireComponent->SetTriggerAxisValue(Axis);
	}
}


void AGrabbable::SetIsBeingGrabbed(bool bGrabbed) 
{
	bIsBeingGrabbed = bGrabbed;
}

