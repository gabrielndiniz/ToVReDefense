// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grabbable.generated.h"

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
	void SetTriggerAxisValue(float Axis) const;

	
private:
	UPROPERTY()
	class UFireWeaponComponent* FireComponent;

	UPROPERTY()
	USkeletalMeshComponent* SkeletalMeshComponent;

	
	UPROPERTY(VisibleAnywhere)
	USceneComponent* GrabbableRootComponent;
	
	UPROPERTY(VisibleAnywhere)
	FTransform MuzzleTransform;
};
