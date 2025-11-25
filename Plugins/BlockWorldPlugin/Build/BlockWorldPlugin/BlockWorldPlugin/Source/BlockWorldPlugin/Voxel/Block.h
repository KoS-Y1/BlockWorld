// Created by y1. All Rights Reserved.


#pragma once

#include "CoreMinimal.h"

#include "BlockType.h"

#include "Block.generated.h"

USTRUCT(BlueprintType, Category = "Voxel")
struct BLOCKWORLDPLUGIN_API FBlock
{
	GENERATED_BODY()

	FBlock() : Type(EBlockType::None) {}

	UPROPERTY(EditAnywhere, Category = "Voxel")
	EBlockType Type;
};
