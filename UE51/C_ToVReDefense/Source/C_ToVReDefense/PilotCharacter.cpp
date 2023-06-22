// Fill out your copyright notice in the Description page of Project Settings.


#include "PilotCharacter.h"

#include "HandController.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
APilotCharacter::APilotCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Capsule = GetCapsuleComponent();

	VRRoot = CreateDefaultSubobject<USceneComponent>(TEXT("VRRoot"));
	VRRoot->SetupAttachment(GetRootComponent());
	
}
void APilotCharacter::BeginPlay()
{
	Super::BeginPlay();

	bDoesHaveHands = SetupHandControllers();

	PlayerController = Cast<APlayerController>(GetController());

	// Set the tracking origin to the floor if using VR
	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
	{
		UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Floor);
	}

	// Calculate the player's height and adjust the capsule and camera accordingly
	CurrentCameraHeight = Capsule->GetScaledCapsuleHalfHeight();
	FVector ActorLocation = GetActorLocation();
	FVector EyeLevelOffsetVector = FVector(0.f, 0.f, CurrentCameraHeight);
	SetActorLocation(ActorLocation + EyeLevelOffsetVector);

	CalculatePlayerHeight();

}
void APilotCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	float NewCameraHeight = Capsule->GetScaledCapsuleHalfHeight();
	if (!FMath::IsNearlyEqual(NewCameraHeight, CurrentCameraHeight, Tolerance))
	{
		CalculatePlayerHeight();
	}
	
}

// Called to bind functionality to input
void APilotCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction(TEXT("LeftFaceButton1"), IE_Pressed, this, &APilotCharacter::LeftFaceButton1Pressed);
	PlayerInputComponent->BindAction(TEXT("LeftFaceButton2"), IE_Pressed, this, &APilotCharacter::LeftFaceButton2Pressed);
	PlayerInputComponent->BindAction(TEXT("RightFaceButton1"), IE_Pressed, this, &APilotCharacter::RightFaceButton1Pressed);
	PlayerInputComponent->BindAction(TEXT("RightFaceButton2"), IE_Pressed, this, &APilotCharacter::RightFaceButton2Pressed);
	PlayerInputComponent->BindAction(TEXT("LeftMenuButton"), IE_Pressed, this, &APilotCharacter::LeftMenuButtonPressed);
	PlayerInputComponent->BindAction(TEXT("RightMenuButton"), IE_Pressed, this, &APilotCharacter::RightMenuButtonPressed);
	PlayerInputComponent->BindAction(TEXT("LeftFaceButton1"), IE_Pressed, this, &APilotCharacter::LeftFaceButton1Pressed);
	PlayerInputComponent->BindAction(TEXT("LeftFaceButton2"), IE_Pressed, this, &APilotCharacter::LeftFaceButton2Pressed);
	PlayerInputComponent->BindAction(TEXT("LeftMenuButton"), IE_Pressed, this, &APilotCharacter::LeftMenuButtonPressed);
	PlayerInputComponent->BindAction(TEXT("RightMenuButton"), IE_Pressed, this, &APilotCharacter::RightMenuButtonPressed);
	PlayerInputComponent->BindAction(TEXT("RightTrigger"), IE_Pressed, this, &APilotCharacter::RightTriggerPressed);
	PlayerInputComponent->BindAction(TEXT("RightGrip"), IE_Pressed, this, &APilotCharacter::RightGripPressed);
	PlayerInputComponent->BindAction(TEXT("LeftTrigger"), IE_Pressed, this, &APilotCharacter::LeftTriggerPressed);
	PlayerInputComponent->BindAction(TEXT("LeftGrip"), IE_Pressed, this, &APilotCharacter::LeftGripPressed);
	PlayerInputComponent->BindAction(TEXT("LeftFaceButton1"), IE_Released, this, &APilotCharacter::LeftFaceButton1Released);
	PlayerInputComponent->BindAction(TEXT("LeftFaceButton2"), IE_Released, this, &APilotCharacter::LeftFaceButton2Released);
	PlayerInputComponent->BindAction(TEXT("RightFaceButton1"), IE_Released, this, &APilotCharacter::RightFaceButton1Released);
	PlayerInputComponent->BindAction(TEXT("RightFaceButton2"), IE_Released, this, &APilotCharacter::RightFaceButton2Released);
	PlayerInputComponent->BindAction(TEXT("LeftMenuButton"), IE_Released, this, &APilotCharacter::LeftMenuButtonReleased);
	PlayerInputComponent->BindAction(TEXT("RightMenuButton"), IE_Released, this, &APilotCharacter::RightMenuButtonReleased);
	PlayerInputComponent->BindAction(TEXT("LeftFaceButton1"), IE_Released, this, &APilotCharacter::LeftFaceButton1Released);
	PlayerInputComponent->BindAction(TEXT("LeftFaceButton2"), IE_Released, this, &APilotCharacter::LeftFaceButton2Released);
	PlayerInputComponent->BindAction(TEXT("LeftMenuButton"), IE_Released, this, &APilotCharacter::LeftMenuButtonReleased);
	PlayerInputComponent->BindAction(TEXT("RightMenuButton"), IE_Released, this, &APilotCharacter::RightMenuButtonReleased);
	PlayerInputComponent->BindAction(TEXT("RightTrigger"), IE_Released, this, &APilotCharacter::RightTriggerReleased);
	PlayerInputComponent->BindAction(TEXT("RightGrip"), IE_Released, this, &APilotCharacter::RightGripReleased);
	PlayerInputComponent->BindAction(TEXT("LeftTrigger"), IE_Released, this, &APilotCharacter::LeftTriggerReleased);
	PlayerInputComponent->BindAction(TEXT("LeftGrip"), IE_Released, this, &APilotCharacter::LeftGripReleased);
	PlayerInputComponent->BindAction(TEXT("RightThumbAnim"), IE_Pressed, this, &APilotCharacter::RightThumbAnimPressed);
	PlayerInputComponent->BindAction(TEXT("LeftThumbAnim"), IE_Pressed, this, &APilotCharacter::LeftThumbAnimPressed);
	PlayerInputComponent->BindAction(TEXT("RightThumbAnim"), IE_Released, this, &APilotCharacter::RightThumbAnimReleased);
	PlayerInputComponent->BindAction(TEXT("LeftThumbAnim"), IE_Released, this, &APilotCharacter::LeftThumbAnimReleased);
	PlayerInputComponent->BindAxis(TEXT("LeftThumbstickY"), this, &APilotCharacter::LeftThumbstickY);
	PlayerInputComponent->BindAxis(TEXT("LeftThumbstickX"), this, &APilotCharacter::LeftThumbstickX);
	PlayerInputComponent->BindAxis(TEXT("LeftTouchpadY"), this, &APilotCharacter::LeftTouchpadY);
	PlayerInputComponent->BindAxis(TEXT("LeftTouchpadX"), this, &APilotCharacter::LeftTouchpadX);
	PlayerInputComponent->BindAxis(TEXT("RightThumbstickY"), this, &APilotCharacter::RightThumbstickY);
	PlayerInputComponent->BindAxis(TEXT("RightThumbstickX"), this, &APilotCharacter::RightThumbstickX);
	PlayerInputComponent->BindAxis(TEXT("RightTouchpadY"), this, &APilotCharacter::RightTouchpadY);
	PlayerInputComponent->BindAxis(TEXT("RightTouchpadX"), this, &APilotCharacter::RightTouchpadX);
	PlayerInputComponent->BindAxis(TEXT("LeftTriggerAxis"), this, &APilotCharacter::LeftTriggerAxis);
	PlayerInputComponent->BindAxis(TEXT("RightTriggerAxis"), this, &APilotCharacter::RightTriggerAxis);
	PlayerInputComponent->BindAxis(TEXT("LeftGripAxis"), this, &APilotCharacter::LeftGripAxis);
	PlayerInputComponent->BindAxis(TEXT("RightGripAxis"), this, &APilotCharacter::RightGripAxis);
	PlayerInputComponent->BindAxis(TEXT("LeftThumbstickY"), this, &APilotCharacter::LeftThumbstickY);
	PlayerInputComponent->BindAxis(TEXT("LeftThumbstickX"), this, &APilotCharacter::LeftThumbstickX);
	PlayerInputComponent->BindAxis(TEXT("RightThumbstickY"), this, &APilotCharacter::RightThumbstickY);
	PlayerInputComponent->BindAxis(TEXT("RightThumbstickX"), this, &APilotCharacter::RightThumbstickX);
	PlayerInputComponent->BindAxis(TEXT("LeftTriggerAxis"), this, &APilotCharacter::LeftTriggerAxis);
	PlayerInputComponent->BindAxis(TEXT("RightTriggerAxis"), this, &APilotCharacter::RightTriggerAxis);
	PlayerInputComponent->BindAxis(TEXT("LeftGripAxis"), this, &APilotCharacter::LeftGripAxis);
	PlayerInputComponent->BindAxis(TEXT("RightGripAxis"), this, &APilotCharacter::RightGripAxis);
	
	



}

float APilotCharacter::GetVRCapsuleHalfHeight()
{
	return Capsule->GetScaledCapsuleHalfHeight();
}

void APilotCharacter::CalculatePlayerHeight()
{
	if (Capsule)
	{
		FVector ViewLocation = GetPawnViewLocation();
		float EyeHeight = ViewLocation.Z - GetActorLocation().Z;
		float CameraDistance = Capsule->GetScaledCapsuleRadius() * 2.0f; // assuming the camera is above the center of the capsule
		float FOVInRadians = 2.0f * FMath::Atan(EyeHeight / CameraDistance);
		//Camera->SetFieldOfView(FMath::RadiansToDegrees(FOVInRadians));
        
		// Set capsule height to player's height
		Capsule->SetCapsuleHalfHeight(EyeHeight);
		VRRoot->SetRelativeLocation(FVector(0,0,-EyeHeight));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Capsule component not found!"));
	}
}

bool APilotCharacter::SetupHandControllers()
{
	if (RightHandControllerClass)
	{
		RightController = GetWorld()->SpawnActor<AHandController>(RightHandControllerClass, FVector::ZeroVector, FRotator::ZeroRotator);
		if (RightController)
		{
			RightController->AttachToComponent(VRRoot, FAttachmentTransformRules::KeepRelativeTransform);
			RightController->SetHand(EControllerHand::Right, RightHandTransform);
			RightController->SetOwner(this);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to spawn right hand controller"));
			return false;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("RightHandControllerClass not set!"));
		return false;
	}

	if (LeftHandControllerClass)
	{
		LeftController = GetWorld()->SpawnActor<AHandController>(LeftHandControllerClass, FVector::ZeroVector, FRotator::ZeroRotator);
		if (LeftController)
		{
			LeftController->AttachToComponent(VRRoot, FAttachmentTransformRules::KeepRelativeTransform);
			LeftController->SetHand(EControllerHand::Left, LeftHandTransform);
			LeftController->SetOwner(this);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to spawn left hand controller"));
			return false;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("LeftHandControllerClass not set!"));
		return false;
	}

	if (LeftController && RightController)
	{
		LeftController->SetPairHand(RightController);
		RightController->SetPairHand(LeftController);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("One of the controllers not found!"));
		return false;
	}
	return true;
}

void APilotCharacter::LeftFaceButton1Pressed()
{
	LeftController->HandFaceButton1Pressed();
}

void APilotCharacter::LeftFaceButton2Pressed()
{
	LeftController->HandFaceButton2Pressed();
}

void APilotCharacter::RightFaceButton1Pressed()
{
	RightController->HandFaceButton1Pressed();
}

void APilotCharacter::RightFaceButton2Pressed()
{
	RightController->HandFaceButton2Pressed();
}

void APilotCharacter::LeftMenuButtonPressed()
{
	LeftController->HandMenuButtonPressed();
}

void APilotCharacter::RightMenuButtonPressed()
{
	RightController->HandMenuButtonPressed();
}

void APilotCharacter::RightTriggerPressed()
{
	RightController->HandTriggerPressed();
}

void APilotCharacter::RightGripPressed()
{
	RightController->HandGripPressed();
}

void APilotCharacter::LeftTriggerPressed()
{
	LeftController->HandTriggerPressed();
}

void APilotCharacter::LeftGripPressed()
{
	LeftController->HandGripPressed();
}

void APilotCharacter::LeftFaceButton1Released()
{
	LeftController->HandFaceButton1Released();
}

void APilotCharacter::LeftFaceButton2Released()
{
	LeftController->HandFaceButton2Released();
}

void APilotCharacter::RightFaceButton1Released()
{
	RightController->HandFaceButton1Released();
}

void APilotCharacter::RightFaceButton2Released()
{
	RightController->HandFaceButton2Released();
}

void APilotCharacter::LeftMenuButtonReleased()
{
	LeftController->HandMenuButtonReleased();
}

void APilotCharacter::RightMenuButtonReleased()
{
	RightController->HandMenuButtonReleased();
}

void APilotCharacter::RightTriggerReleased()
{
	RightController->HandTriggerReleased();
}

void APilotCharacter::RightGripReleased()
{
	RightController->HandGripReleased();
}

void APilotCharacter::LeftTriggerReleased()
{
	LeftController->HandTriggerReleased();
}

void APilotCharacter::LeftGripReleased()
{
	LeftController->HandGripReleased();
}

void APilotCharacter::RightThumbAnimPressed()
{
	RightController->ThumbAnimPressed();
}

void APilotCharacter::LeftThumbAnimPressed()
{
	LeftController->ThumbAnimPressed();
}

void APilotCharacter::RightThumbAnimReleased()
{
	RightController->ThumbAnimReleased();
}

void APilotCharacter::LeftThumbAnimReleased()
{
	LeftController->ThumbAnimReleased();
}

void APilotCharacter::LeftThumbstickY(float AxisValue)
{
	LeftController->HandThumbstickY(AxisValue);
}

void APilotCharacter::LeftThumbstickX(float AxisValue)
{
	LeftController->HandThumbstickX(AxisValue);
	
}

void APilotCharacter::LeftTouchpadY(float AxisValue)
{
	LeftController->HandTouchpadY(AxisValue);
}

void APilotCharacter::LeftTouchpadX(float AxisValue)
{
	LeftController->HandTouchpadX(AxisValue);
}

void APilotCharacter::RightThumbstickY(float AxisValue)
{
	RightController->HandThumbstickY(AxisValue);
}

void APilotCharacter::RightThumbstickX(float AxisValue)
{
	
	RightController->HandThumbstickX(AxisValue);

	
}

void APilotCharacter::RightTouchpadY(float AxisValue)
{
	RightController->HandTouchpadY(AxisValue);
}

void APilotCharacter::RightTouchpadX(float AxisValue)
{
	RightController->HandTouchpadX(AxisValue);
}

void APilotCharacter::LeftTriggerAxis(float AxisValue)
{
	LeftController->HandTriggerAxis(AxisValue);
}

void APilotCharacter::RightTriggerAxis(float AxisValue)
{
	RightController->HandTriggerAxis(AxisValue);
}

void APilotCharacter::LeftGripAxis(float AxisValue)
{
	LeftController->HandGripAxis(AxisValue);
}

void APilotCharacter::RightGripAxis(float AxisValue)
{
	RightController->HandGripAxis(AxisValue);
}


