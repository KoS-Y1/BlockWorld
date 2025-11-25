// Created by y1. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "Block.h"

#include "BlockLandDataAsset.generated.h"

UCLASS(BlueprintType)
class BLOCKWORLDPLUGIN_API UBlockLandDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SizeX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SizeY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FBlock> Blocks;

	UPROPERTY(EditAnywhere)
	float ErosionProbability;
	
	UPROPERTY(EditAnywhere)
	int32 ErosionDepth;

	UFUNCTION(BlueprintCallable)
	void SetBlock(int32 Idx, EBlockType Type);
	void SetBlock(int32 X, int32 Y, EBlockType Type);

	void RandomlyErodeEdges();

	UFUNCTION(BlueprintCallable)
	[[nodiscard]] EBlockType GetBlockType(int32 Idx) const;
	[[nodiscard]] EBlockType GetBlockType(int32 X, int32 Y) const;
	[[nodiscard]] FBlock GetBlock(int32 Idx) const;
	[[nodiscard]] FBlock GetBlock(int32 X, int32 Y) const;

private:
	bool IsAdjacentToNone(int32 Idx) const;
	bool IsAdjacentToNone(int32 X, int32 Y) const;
};
