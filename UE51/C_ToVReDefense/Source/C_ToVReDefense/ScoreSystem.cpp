#include "ScoreSystem.h"
#include "Kismet/GameplayStatics.h"


void UScoreSystem::SaveScore()
{
	UGameplayStatics::SaveGameToSlot(this, SaveSlotName, UserIndex);
}

void UScoreSystem::LoadScore()
{
	UScoreSystem* LoadedData = Cast<UScoreSystem>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex));
	if (LoadedData)
	{
		Score = LoadedData->Score;
	}
}

void UScoreSystem::SetScore(int32 Points)
{
	if(Score<Points)
	{
		Score = Points;
	}
}

int32 UScoreSystem::GetScore() const
{
	return Score;
}