// Created by y1. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "BlockWorldDataAssets.generated.h"

class UBlockLandDataAsset;
UCLASS(BlueprintType)
class BLOCKWORLDPLUGIN_API UBlockWorldDataAssets : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 LandCout;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UBlockLandDataAsset*> LandData;
	
private:
};
