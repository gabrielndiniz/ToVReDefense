// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HandController.generated.h"

UENUM(BlueprintType)
enum class HandToUse : uint8
{
	LeftHand,
	RightHand
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHandGripEvent);

UCLASS()
class C_TOVREDEFENSE_API AHandController : public AActor
{
	GENERATED_BODY()
	
	
public:	
	// Sets default values for this actor's properties
	AHandController();


	void SetHand(EControllerHand ControllerHand, FTransform HandTransform);

	
	void SetPairHand(AHandController* HandController) {PairHandController = HandController;}

	UFUNCTION(BlueprintPure, Category = "Config")
	AHandController* GetPairHand() {return PairHandController; }
	
	UFUNCTION()
	void HandFaceButton1Pressed();
	UFUNCTION()
	void HandFaceButton2Pressed();
	UFUNCTION() 
	void HandMenuButtonPressed();
	UFUNCTION() 
	void HandTriggerPressed();
	UFUNCTION() 
	void HandGripPressed();
	UFUNCTION()
	void HandFaceButton1Released();
	UFUNCTION()
	void HandFaceButton2Released();
	UFUNCTION() 
	void HandMenuButtonReleased();
	UFUNCTION() 
	void HandTriggerReleased();
	UFUNCTION() 
	void HandGripReleased();
	UFUNCTION() 
	void ThumbAnimPressed();
	UFUNCTION() 
	void ThumbAnimReleased();

	UFUNCTION() 
	void HandThumbstickY(float AxisValue);
	UFUNCTION() 
	void HandThumbstickX(float AxisValue);
	UFUNCTION() 
	void HandTouchpadY(float AxisValue);
	UFUNCTION() 
	void HandTouchpadX(float AxisValue);
	UFUNCTION() 
	void HandTriggerAxis(float AxisValue);
	UFUNCTION() 
	void HandGripAxis(float AxisValue);

	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* HandMeshComponent;

	UFUNCTION(BlueprintCallable, Category = "Hand Animations")
	void SetGripAnimation(bool bNewGripAnim) { bGripAnim = bNewGripAnim; }

	UFUNCTION(BlueprintPure, Category = "Hand Animations")
	bool GetGripAnimation() const { return bGripAnim; }
	

	UFUNCTION(BlueprintCallable, Category = "Hand Animations")
	void SetPointAnimation(bool bNewPointAnim) { bPointAnim = bNewPointAnim; }

	UFUNCTION(BlueprintPure, Category = "Hand Animations")
	bool GetPointAnimation() const { return bPointAnim; }
	

	UFUNCTION(BlueprintCallable, Category = "Hand Animations")
	void SetThumbsAnimation(bool bNewThumbsAnim) { bThumbsAnim = bNewThumbsAnim; }

	UFUNCTION(BlueprintPure, Category = "Hand Animations")
	bool GetThumbsAnimation() const { return bThumbsAnim; }

	UPROPERTY(BlueprintAssignable, Category = "Hand Animations")
	FHandGripEvent OnHandGripEvent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UMotionControllerComponent* MotionController;
	
	//Status	
	UFUNCTION(BlueprintPure, Category = "Config")
	bool BIsRightHand();
	
private:
	//Components

	UPROPERTY()
	EControllerHand ThisControllerHand;

	UPROPERTY()
	bool bIsGrabbing = false;

	UPROPERTY(EditDefaultsOnly, Category = "Hand Animations")
	USkeletalMesh* RightHandMesh;
	
	UPROPERTY(EditDefaultsOnly, Category = "Hand Animations")
	USkeletalMesh* LeftHandMesh;
	

	UPROPERTY(VisibleAnywhere)
	AHandController* PairHandController;

	UPROPERTY(VisibleAnywhere)
	HandToUse ThisHand = HandToUse::RightHand;



	//Status
	bool bGripAnim = false;
	bool bPointAnim = false;	
	bool bThumbsAnim = false;
	
	
	void PlayHapticEffect();

};
