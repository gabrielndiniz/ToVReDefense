// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WidgetInteractorComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class C_TOVREDEFENSE_API UWidgetInteractorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWidgetInteractorComponent();

	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
	UFUNCTION()
	void SetTriggerAxisValue(float NewTriggerAxisValue);
	
	UFUNCTION(BlueprintPure, Category = "Widget Interaction")
	float GetTriggerAxisValue() const {return TriggerAxisValue;}

	
	UFUNCTION(BlueprintCallable, Category = "Widget Interaction")
	void SetPointer(class UWidgetInteractionComponent* NewPointer) {Pointer = NewPointer; }

private:
	UPROPERTY()
	float TriggerAxisValue = 0;

	
	UPROPERTY(VisibleAnywhere)
	class UWidgetInteractionComponent* Pointer;

	
	UPROPERTY()
	bool bStartClick = false;
		
};
