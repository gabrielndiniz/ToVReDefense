// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HandController.h"
#include "PilotCharacter.generated.h"

UCLASS()
class C_TOVREDEFENSE_API APilotCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APilotCharacter();
	void CalculatePlayerHeight();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	

	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	USceneComponent* CameraAttachment;

	UFUNCTION(BlueprintPure, Category = "Config")
	class UCameraComponent* GetCameraComponent() const { return Camera; }

	
	UFUNCTION(BlueprintPure, Category = "Config")
	FTransform GetCameraTransform() const;

private:
	UFUNCTION()
	bool SetupHandControllers();
	
	UFUNCTION()
	void LeftFaceButton1Pressed();
	UFUNCTION()
	void LeftFaceButton2Pressed();
	UFUNCTION()
	void RightFaceButton1Pressed();
	UFUNCTION() 
	void RightFaceButton2Pressed();
	UFUNCTION() 
	void LeftMenuButtonPressed();
	UFUNCTION() 
	void RightMenuButtonPressed();
	UFUNCTION() 
	void RightTriggerPressed();
	UFUNCTION() 
	void RightGripPressed();
	UFUNCTION() 
	void LeftTriggerPressed();
	UFUNCTION() 
	void LeftGripPressed();
	UFUNCTION()
	void LeftFaceButton1Released();
	UFUNCTION()
	void LeftFaceButton2Released();
	UFUNCTION()
	void RightFaceButton1Released();
	UFUNCTION() 
	void RightFaceButton2Released();
	UFUNCTION() 
	void LeftMenuButtonReleased();
	UFUNCTION() 
	void RightMenuButtonReleased();
	UFUNCTION() 
	void RightTriggerReleased();
	UFUNCTION() 
	void RightGripReleased();
	UFUNCTION() 
	void LeftTriggerReleased();
	UFUNCTION() 
	void LeftGripReleased(); 
	UFUNCTION() 
	void RightThumbAnimPressed(); 
	UFUNCTION() 
	void LeftThumbAnimPressed(); 
	UFUNCTION() 
	void RightThumbAnimReleased(); 
	UFUNCTION() 
	void LeftThumbAnimReleased(); 

	UFUNCTION() 
	void LeftThumbstickY(float AxisValue);
	UFUNCTION() 
	void LeftThumbstickX(float AxisValue);
	UFUNCTION() 
	void LeftTouchpadY(float AxisValue);
	UFUNCTION() 
	void LeftTouchpadX(float AxisValue);
	UFUNCTION() 
	void RightThumbstickY(float AxisValue);
	UFUNCTION() 
	void RightThumbstickX(float AxisValue);
	UFUNCTION() 
	void RightTouchpadY(float AxisValue);
	UFUNCTION() 
	void RightTouchpadX(float AxisValue);
	UFUNCTION() 
	void LeftTriggerAxis(float AxisValue);
	UFUNCTION() 
	void RightTriggerAxis(float AxisValue);
	UFUNCTION() 
	void LeftGripAxis(float AxisValue);
	UFUNCTION() 
	void RightGripAxis(float AxisValue);



	//Components

	UPROPERTY()
	class AHandController* LeftController;
	
	UPROPERTY()
	class AHandController* RightController;

	UPROPERTY()
	class USceneComponent* VRRoot;

	UPROPERTY()
	class UCapsuleComponent* Capsule;
	
	UPROPERTY()
	class UCameraComponent* Camera;

	
	UPROPERTY()
	bool bDoesHaveHands = false;



	UPROPERTY(EditDefaultsOnly)
	float Tolerance = KINDA_SMALL_NUMBER;
	
	UPROPERTY()
	float CurrentCameraHeight;

	UPROPERTY()
	APlayerController* PlayerController;
	
	//config
	UPROPERTY(EditAnywhere, Category="VR Controller")
	TSubclassOf<AHandController> RightHandControllerClass;

	UPROPERTY(EditAnywhere, Category="VR Controller")
	TSubclassOf<AHandController> LeftHandControllerClass;

	
	UPROPERTY(EditAnywhere, Category="VR Controller")
	FTransform RightHandTransform = FTransform::Identity;
	
	UPROPERTY(EditAnywhere, Category="VR Controller")
	FTransform LeftHandTransform = FTransform::Identity;

};
