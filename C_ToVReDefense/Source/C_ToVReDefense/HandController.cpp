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
		}
		ThisHand = HandToUse::RightHand;
	}
	else
	{
		if (LeftHandMesh)
		{
			HandMeshComponent->SetSkeletalMesh(LeftHandMesh);
			HandMeshComponent->SetRelativeTransform(HandTransform);
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
}

void AHandController::HandFaceButton1Pressed()
{
    UE_LOG(LogTemp, Display, TEXT("HandFaceButton1Pressed"));
}

void AHandController::HandFaceButton2Pressed()
{
    UE_LOG(LogTemp, Display, TEXT("HandFaceButton2Pressed"));
}

void AHandController::HandMenuButtonPressed()
{
    UE_LOG(LogTemp, Display, TEXT("HandMenuButtonPressed"));
}

void AHandController::HandTriggerPressed()
{
    UE_LOG(LogTemp, Display, TEXT("HandTriggerPressed"));
	bPointAnim = true;
}

void AHandController::HandGripPressed()
{
    UE_LOG(LogTemp, Display, TEXT("HandGripPressed"));
	bGripAnim = true;

	OnHandGripEvent.Broadcast();
}

void AHandController::HandFaceButton1Released()
{
    UE_LOG(LogTemp, Display, TEXT("HandFaceButton1Released"));
}

void AHandController::HandFaceButton2Released()
{
    UE_LOG(LogTemp, Display, TEXT("HandFaceButton2Released"));
}

void AHandController::HandMenuButtonReleased()
{
    UE_LOG(LogTemp, Display, TEXT("HandMenuButtonReleased"));
}

void AHandController::HandTriggerReleased()
{
    UE_LOG(LogTemp, Display, TEXT("HandTriggerReleased"));
	bPointAnim = false;
}

void AHandController::HandGripReleased()
{
    UE_LOG(LogTemp, Display, TEXT("HandGripReleased"));
	bGripAnim = false;

	OnHandGripEvent.Broadcast();
}

void AHandController::ThumbAnimPressed()
{
	UE_LOG(LogTemp, Display, TEXT("ThumbAnimPressed"));
	bThumbsAnim = true;
}

void AHandController::ThumbAnimReleased()
{
	UE_LOG(LogTemp, Display, TEXT("ThumbAnimReleased"));
	bThumbsAnim = false;
}

void AHandController::HandThumbstickY(float AxisValue)
{
    if (FMath::Abs(AxisValue) >= 0.5f)
    {
        UE_LOG(LogTemp, Display, TEXT("HandThumbstickY: %f"), AxisValue);
    }
}

void AHandController::HandThumbstickX(float AxisValue)
{
    if (FMath::Abs(AxisValue) >= 0.5f)
    {
        UE_LOG(LogTemp, Display, TEXT("HandThumbstickX: %f"), AxisValue);
    }
}

void AHandController::HandTouchpadY(float AxisValue)
{
    if (FMath::Abs(AxisValue) >= 0.5f)
    {
        UE_LOG(LogTemp, Display, TEXT("HandTouchpadY: %f"), AxisValue);
    }
}

void AHandController::HandTouchpadX(float AxisValue)
{
    if (FMath::Abs(AxisValue) >= 0.5f)
    {
        UE_LOG(LogTemp, Display, TEXT("HandTouchpadX: %f"), AxisValue);
    }
}

void AHandController::HandTriggerAxis(float AxisValue)
{
    if (FMath::Abs(AxisValue) >= 0.5f)
    {
        UE_LOG(LogTemp, Display, TEXT("HandTriggerAxis: %f"), AxisValue);
    }
}

void AHandController::HandGripAxis(float AxisValue)
{
    if (FMath::Abs(AxisValue) >= 0.5f)
    {
        UE_LOG(LogTemp, Display, TEXT("HandGripAxis: %f"), AxisValue);
    }
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
	UE_LOG(LogTemp, Display, TEXT("Error f$4 There is no EControllerHand"));
	return false;
}

void AHandController::PlayHapticEffect()
{
}
