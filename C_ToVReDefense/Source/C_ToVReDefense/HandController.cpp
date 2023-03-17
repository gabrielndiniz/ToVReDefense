// Fill out your copyright notice in the Description page of Project Settings.


#include "HandController.h"

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

	if (BIsRightHand())
	{
		if (RightHandMesh)
		{
			HandMeshComponent->SetSkeletalMesh(RightHandMesh);
			HandMeshComponent->SetRelativeTransform(HandTransform);
			if (HandMeshComponent->GetNumMaterials() > 0 && RightHandMaterial != nullptr)
			{
				HandMeshComponent->SetMaterial(0, RightHandMaterial);
			}
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
	bPointAnim = false;
	bGripAnim = true;

	if (bSciFiPistolHoldAnim)
	{
		bSciFiPistolShootAnim = true;
	}
}

void AHandController::HandGripPressed()
{
	bGripAnim = true;

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
	bPointAnim = true;
	bSciFiPistolShootAnim = false;
}

void AHandController::HandGripReleased()
{
	bGripAnim = false;
	bThumbsPointAnim = false;
	bSilverKnifeHoldAnim = false;
	bSciFiPistolHoldAnim = false;
	bSciFiPistolShootAnim = false;

	OnHandGripEvent.Broadcast();
}

void AHandController::ThumbAnimPressed()
{
	bThumbsAnim = true;
}

void AHandController::ThumbAnimReleased()
{
	bThumbsAnim = false;
}

void AHandController::HandThumbstickY(float AxisValue)
{
    if (FMath::Abs(AxisValue) >= 0.5f)
    {
    }
}

void AHandController::HandThumbstickX(float AxisValue)
{
    if (FMath::Abs(AxisValue) >= 0.5f)
    {
    }
}

void AHandController::HandTouchpadY(float AxisValue)
{
    if (FMath::Abs(AxisValue) >= 0.5f)
    {
    }
}

void AHandController::HandTouchpadX(float AxisValue)
{
    if (FMath::Abs(AxisValue) >= 0.5f)
    {
    }
}

void AHandController::HandTriggerAxis(float AxisValue)
{
    if (FMath::Abs(AxisValue) >= 0.5f)
    {
    }
}

void AHandController::HandGripAxis(float AxisValue)
{
    /*if (FMath::Abs(AxisValue) >= 0.3f && FMath::Abs(AxisValue) >= 0.7f)
    {
    	
    	bThumbsPointAnim = true;
    }
	if (FMath::Abs(AxisValue) >= 0.7f)
    {
    	
		bGripAnim = true;
		bThumbsPointAnim = false;
		
		OnHandGripEvent.Broadcast();
    }
	if (FMath::Abs(AxisValue) < 0.3f)
	{
    	
		bGripAnim = false;
		bThumbsPointAnim = false;
		bSilverKnifeHoldAnim = false;
		bSciFiPistolHoldAnim = false;
		bSciFiPistolShootAnim = false;
		
		OnHandGripEvent.Broadcast();
	}*/
}


bool AHandController::BIsRightHand()
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
