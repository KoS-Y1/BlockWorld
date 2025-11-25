//
// Created by y1 on 2025-11-22.
//


#include "Randomizer.h"

TWeakObjectPtr<URandomizer> URandomizer::Instance = nullptr;

void URandomizer::Initialize(int32 InSeed)
{
	Seed = InSeed;
	RandomStream.Initialize(Seed);
}

URandomizer* URandomizer::GetInstance()
{
	if (!Instance.IsValid())
	{
		Instance = NewObject<URandomizer>();
		Instance->AddToRoot();
	}

	return Instance.Get();
}

float URandomizer::RandomFloat(float Min, float Max)
{
	return RandomStream.FRandRange(Min, Max);
}

int32 URandomizer::RandomInt(int32 Min, int32 Max)
{
	return RandomStream.FRandRange(Min, Max);
}