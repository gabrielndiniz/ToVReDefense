// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "EnemyPawn.h"
#include "TimerManager.h"
#include "BehaviorTree/BehaviorTree.h"

AEnemyAIController::AEnemyAIController()
{
	
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviourTree"));
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	// Set the timer to check for other tanks every 0.5 seconds
	GetWorldTimerManager().SetTimer(CheckTanksTimerHandle, this, &AEnemyAIController::CheckForOtherTanks, 0.5f, true);
	EnemyPawn = Cast<AEnemyPawn>(GetPawn());
	

}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	BehaviorTreeComponent->StartLogic();
}

void AEnemyAIController::CheckForOtherTanks()
{
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn)
	{
		TArray<AActor*> OverlappingActors;
		ControlledPawn->GetOverlappingActors(OverlappingActors, AEnemyPawn::StaticClass());
		for (AActor* Actor : OverlappingActors)
		{
			if (Actor != ControlledPawn)
			{
				FVector PawnLocation = ControlledPawn->GetActorLocation();
				FVector OtherLocation = Actor->GetActorLocation();
				float Distance = FVector::Distance(PawnLocation, OtherLocation);
				if (Distance <= MaxDistance) 
				{
					// Stop movement if another tank is too close
					if (EnemyPawn)
					{
						if (!BehaviorTreeComponent->IsRunning())
						{
							BehaviorTreeComponent->RestartLogic();
						}
					}
				}

			}
		}
	}
}