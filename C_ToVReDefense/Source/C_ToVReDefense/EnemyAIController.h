// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class C_TOVREDEFENSE_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

	
public:
	AEnemyAIController();
	virtual void BeginPlay() override;
	void CheckForOtherTanks();

	
protected:
	UPROPERTY(EditDefaultsOnly)
	class UBehaviorTreeComponent* BehaviorTreeComponent;

	virtual void OnPossess(APawn* InPawn) override;

private:
	FTimerHandle CheckTanksTimerHandle;
	float MaxDistance = 50;
	class AEnemyPawn* EnemyPawn;
};
