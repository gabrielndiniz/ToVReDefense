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
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSetHandEvent);

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

	
	UFUNCTION(BlueprintCallable, Category = "Hand Animations")
	void SetGrip(bool bNewGripAnim) { bGrip = bNewGripAnim; }

	UFUNCTION(BlueprintPure, Category = "Hand Animations")
	bool GetGrip() const { return bGrip; }
	

	UFUNCTION(BlueprintCallable, Category = "Hand Animations")
	void SetIndex(bool bNewPointAnim) { bIndex = bNewPointAnim; }

	UFUNCTION(BlueprintPure, Category = "Hand Animations")
	bool GetIndex() const { return bIndex; }
	

	UFUNCTION(BlueprintCallable, Category = "Hand Animations")
	void SetThumbs(bool bNewThumbsAnim) { bThumbs = bNewThumbsAnim; }

	UFUNCTION(BlueprintPure, Category = "Hand Animations")
	bool GetThumbs() const { return bThumbs; }
	

	UFUNCTION(BlueprintCallable, Category = "Hand Animations")
	void SetHold(bool bNewThumbsPointAnim) { bHold = bNewThumbsPointAnim; }

	UFUNCTION(BlueprintPure, Category = "Hand Animations")
	bool GetHold() const { return bHold; }
	
	UFUNCTION(BlueprintPure, Category = "Hand Animations")
	float GetGripAxis() const { return GripAxis; }
	
	UFUNCTION(BlueprintPure, Category = "Hand Animations")
	float GetTriggerAxis() const { return TriggerAxis; }

	UFUNCTION(BlueprintPure, Category = "Config")
	class UMotionControllerComponent* GetMotionController() const { return MotionController; }

	UFUNCTION(BlueprintPure, Category = "Config")
	USkeletalMeshComponent* GetHandMeshComponent() const { return HandMeshComponent; }

	UPROPERTY(BlueprintAssignable, Category = "Hand Animations")
	FHandGripEvent OnHandGripEvent;
	
	UPROPERTY(BlueprintAssignable, Category = "Config")
	FSetHandEvent OnSetHandEvent;

	UFUNCTION(BlueprintCallable, Category = "Hand Animations")
	void SetIsGrabbing(const bool bGrabbing, AActor* Grabbed);

	UFUNCTION(BlueprintPure, Category = "Hand Animations")
	bool GetIsGrabbing() const { return bIsGrabbing; }
	
	
	//Status	
	UFUNCTION(BlueprintPure, Category = "Config")
	bool IsRightHand() const;
	
private:
	//Components

	UPROPERTY()
	EControllerHand ThisControllerHand;
	
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* HandMeshComponent;

	UPROPERTY()
	bool bIsGrabbing = false;

	UPROPERTY(EditDefaultsOnly, Category = "Hand Animations")
	USkeletalMesh* RightHandMesh;
	
	UPROPERTY(EditDefaultsOnly, Category = "Hand Animations")
	USkeletalMesh* LeftHandMesh;

	

	UPROPERTY(EditDefaultsOnly, Category = "Hand Animations")
	UMaterialInterface* RightHandMaterial;
	
	UPROPERTY(EditDefaultsOnly, Category = "Hand Animations")
	UMaterialInterface* LeftHandMaterial;
	
	UPROPERTY(VisibleAnywhere)
	class UMotionControllerComponent* MotionController;
	

	UPROPERTY(VisibleAnywhere)
	AHandController* PairHandController;
	
	UPROPERTY(VisibleAnywhere)
	class AGrabbable* GrabbedItem;
	
	UPROPERTY(VisibleAnywhere)
	HandToUse ThisHand = HandToUse::RightHand;



	//Status
	bool bGrip = false;
	bool bIndex = false;	
	bool bThumbs = false;
	bool bHold = false;
	float GripAxis = 0;
	float TriggerAxis = 0;
	
	

};
