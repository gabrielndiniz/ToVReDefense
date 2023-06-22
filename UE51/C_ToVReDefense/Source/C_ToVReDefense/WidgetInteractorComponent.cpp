// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetInteractorComponent.h"

#include "Components/WidgetInteractionComponent.h"

// Sets default values for this component's properties
UWidgetInteractorComponent::UWidgetInteractorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWidgetInteractorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UWidgetInteractorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UWidgetInteractorComponent::SetTriggerAxisValue(float NewTriggerAxisValue)
{
	TriggerAxisValue = NewTriggerAxisValue;
	if (NewTriggerAxisValue > 0.9)
	{
		Pointer->PressPointerKey(EKeys::LeftMouseButton);
		bStartClick = true;
	}
	if (NewTriggerAxisValue < 0.2 && bStartClick)
	{
		Pointer->ReleasePointerKey(EKeys::LeftMouseButton);
		bStartClick = false;
	}
}

