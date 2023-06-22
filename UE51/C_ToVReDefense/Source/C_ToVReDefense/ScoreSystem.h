// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ScoreSystem.generated.h"

/**
 * 
 */
UCLASS()
class C_TOVREDEFENSE_API UScoreSystem : public USaveGame
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	void SaveScore();

	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	void LoadScore();
	
	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	void SetScore(int32 Points);
	
	UFUNCTION(BlueprintPure, Category = "SaveGame")
	int32 GetScore() const;

private:
	UPROPERTY(VisibleAnywhere, Category = "SaveGame")
	int32 Score = 0;

	UPROPERTY()
	int32 UserIndex = 0;

	UPROPERTY()
	FString SaveSlotName = TEXT("ScoreSaveSlot");;

};
