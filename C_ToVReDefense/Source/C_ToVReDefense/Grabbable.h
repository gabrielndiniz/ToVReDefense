// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grabbable.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FChangeGrab);

UCLASS()
class C_TOVREDEFENSE_API AGrabbable : public AActor
{
	GENERATED_BODY()
	
	
public:	
	// Sets default values for this actor's properties
	AGrabbable();


protected:
	virtual void BeginPlay() override;
	
public:
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void SetTriggerAxisValue(float Axis);

	UFUNCTION(BlueprintPure, Category = "Fire Weapon")
	float GetTriggerAxisValue() const {return TriggerAxisValue;}
	
	UFUNCTION(BlueprintPure, Category = "Fire Weapon")
	class UFireWeaponComponent* GetFireComponent() const {return FireComponent;}
	
	UPROPERTY(BlueprintAssignable, Category = "Config")
	FChangeGrab ChangeGrab;
	
	UFUNCTION()
	void SetIsBeingGrabbed(bool bGrabbed);
	
	UFUNCTION(BlueprintPure, Category = "Fire Weapon")
	bool GetIsForRightHand() const {return bIsForRightHand;}
	
	UFUNCTION()
	USceneComponent* GetConnection() const {return Connection;}
private:
	
	UPROPERTY(VisibleAnywhere, Category = "Config")
	USceneComponent* Connection = nullptr;
	
	UPROPERTY()
	UFireWeaponComponent* FireComponent;
	
	UPROPERTY(VisibleAnywhere)
	USceneComponent* GrabbableRootComponent;
	
	UPROPERTY(VisibleAnywhere)
	FTransform MuzzleTransform;
	
	UPROPERTY(EditAnywhere)
	bool bIsForRightHand = true;
	
	UPROPERTY()
	float TriggerAxisValue;
	

	UPROPERTY()
	bool bIsBeingGrabbed = false;
	
};

