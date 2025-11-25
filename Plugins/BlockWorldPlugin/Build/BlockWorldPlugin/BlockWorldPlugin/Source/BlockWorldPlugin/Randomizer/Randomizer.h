//
// Created by y1 on 2025-11-22.
//

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"

#include "Randomizer.generated.h"

UCLASS(Blueprintable, Category = "Randomizer")
class BLOCKWORLDPLUGIN_API URandomizer : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Randomizer")
	void Initialize(int32 InSeed);

	UFUNCTION(BlueprintCallable, Category = "Randomizer")
	static URandomizer* GetInstance();

	UFUNCTION(BlueprintCallable, Category = "Randomizer")
	float RandomFloat(float Min = 0.0f, float Max = 1.0f);

	UFUNCTION(BlueprintCallable, Category = "Randomizer")
	int32 RandomInt(int32 Min, int32 Max);

	[[nodiscard]] int32 GetSeed() const {return Seed;}

private:
	static TWeakObjectPtr<URandomizer> Instance;
	FRandomStream RandomStream;

	UPROPERTY(EditAnywhere, Category = "Randomizer")
	int32 Seed;
	
};
