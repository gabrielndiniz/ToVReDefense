// Fill out your copyright notice in the Description page of Project Settings.


#include "HandController.h"

#include "Grabbable.h"
#include "MotionControllerComponent.h"

// Sets default values
AHandController::AHandController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionController"));
	SetRootComponent(MotionController);

	HandMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HandMesh"));
	HandMeshComponent->SetupAttachment(MotionController);
}

void AHandController::SetHand(EControllerHand ControllerHand, FTransform HandTransform)
{
	ThisControllerHand = ControllerHand;

	if (IsRightHand())
	{
		if (RightHandMesh)
		{
			HandMeshComponent->SetSkeletalMesh(RightHandMesh);
			HandMeshComponent->SetRelativeTransform(HandTransform);
			if (HandMeshComponent->GetNumMaterials() > 0 && RightHandMaterial != nullptr)
			{
				HandMeshComponent->SetMaterial(0, RightHandMaterial);
			}
			HandMeshComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
		}
		ThisHand = HandToUse::RightHand;
	}
	else
	{
		if (LeftHandMesh)
		{
			HandMeshComponent->SetSkeletalMesh(LeftHandMesh);
			HandMeshComponent->SetRelativeTransform(HandTransform);
			if (HandMeshComponent->GetNumMaterials() > 0 && LeftHandMaterial != nullptr)
			{
				HandMeshComponent->SetMaterial(0, LeftHandMaterial);
			}
			HandMeshComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
		}
		else
		{
			// If there is no left hand mesh, set the skeletal mesh to null
			HandMeshComponent->SetSkeletalMesh(nullptr);
		}
        
		ThisHand = HandToUse::LeftHand;
	}

	HandMeshComponent->RegisterComponent();

	MotionController->SetTrackingSource(ControllerHand);
	MotionController->bDisplayDeviceModel = false;
	OnSetHandEvent.Broadcast();
}

void AHandController::HandFaceButton1Pressed()
{
}

void AHandController::HandFaceButton2Pressed()
{
}

void AHandController::HandMenuButtonPressed()
{
}

void AHandController::HandTriggerPressed()
{
	bIndex = true;
}

void AHandController::HandGripPressed()
{
	bGrip = true;

	OnHandGripEvent.Broadcast();
}

void AHandController::HandFaceButton1Released()
{
}

void AHandController::HandFaceButton2Released()
{
}

void AHandController::HandMenuButtonReleased()
{
}

void AHandController::HandTriggerReleased()
{
	bIndex = false;
}

void AHandController::HandGripReleased()
{
	bGrip = false;
	bHold = false;

	OnHandGripEvent.Broadcast();
}

void AHandController::ThumbAnimPressed()
{
	bThumbs = true;
}

void AHandController::ThumbAnimReleased()
{
	bThumbs = false;
}

void AHandController::HandThumbstickY(float AxisValue)
{
}

void AHandController::HandThumbstickX(float AxisValue)
{
}

void AHandController::HandTouchpadY(float AxisValue)
{
}

void AHandController::HandTouchpadX(float AxisValue)
{
    if (AxisValue >= 0.5f)
    {
    }
}

void AHandController::HandTriggerAxis(float AxisValue)
{
	TriggerAxis = AxisValue;
    if (AxisValue >= 0.9f)
    {
    	bIndex = true;
    }

	if (GrabbedItem && bIsGrabbing)
	{
		GrabbedItem->SetTriggerAxisValue(AxisValue);
	}
}

void AHandController::HandGripAxis(float AxisValue)
{
		GripAxis = AxisValue;
	if (AxisValue >= 0.9f)
    {
		bGrip = true;
		
		OnHandGripEvent.Broadcast();
		return;
    }
	if (AxisValue < 0.2 && AxisValue > 0.1)
	{
		bGrip = false;
		
		OnHandGripEvent.Broadcast();
		return;
	}
	bGrip = false;
}


void AHandController::SetIsGrabbing(const bool bGrabbing, AActor* Grabbed)
{
	bIsGrabbing = bGrabbing;
	GrabbedItem = Cast<AGrabbable>(Grabbed);
	if (!GrabbedItem && bIsGrabbing)
	{
		UE_LOG(LogTemp, Error, TEXT("error z9A@: Item is not Grabbable"));
	}
}

bool AHandController::IsRightHand() const
{
	if (ThisControllerHand == EControllerHand::Right)
	{
		return true;
	}
	else if (ThisControllerHand == EControllerHand::Left)
	{
		return false;
	}
	UE_LOG(LogTemp, Warning, TEXT("Error f$4 There is no EControllerHand"));
	return false;
}

void AHandController::PlayHapticEffect()
{
}
