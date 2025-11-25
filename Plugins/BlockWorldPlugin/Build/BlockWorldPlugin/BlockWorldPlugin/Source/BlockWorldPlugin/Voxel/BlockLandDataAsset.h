// Created by y1. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "Block.h"

#include "BlockLandDataAsset.generated.h"

UCLASS(BlueprintType, Category = "Voxel")
class BLOCKWORLDPLUGIN_API UBlockLandDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voxel")
	int32 SizeX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voxel")
	int32 SizeY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voxel")
	TArray<FBlock> Blocks;

	UPROPERTY(EditAnywhere, Category = "Voxel")
	float ErosionProbability;
	
	UPROPERTY(EditAnywhere, Category = "Voxel")
	int32 ErosionDepth;

	UFUNCTION(BlueprintCallable, Category = "Voxel")
	void SetBlock(int32 Idx, EBlockType Type);
	void SetBlock(int32 X, int32 Y, EBlockType Type);

	void RandomlyErodeEdges();

	UFUNCTION(BlueprintCallable, Category = "Voxel")
	[[nodiscard]] EBlockType GetBlockType(int32 Idx) const;
	[[nodiscard]] EBlockType GetBlockType(int32 X, int32 Y) const;
	[[nodiscard]] FBlock GetBlock(int32 Idx) const;
	[[nodiscard]] FBlock GetBlock(int32 X, int32 Y) const;

private:
	bool IsAdjacentToNone(int32 Idx) const;
	bool IsAdjacentToNone(int32 X, int32 Y) const;
};
