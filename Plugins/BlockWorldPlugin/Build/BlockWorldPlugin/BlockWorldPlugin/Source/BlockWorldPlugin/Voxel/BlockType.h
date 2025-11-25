// Created by y1. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "BlockType.generated.h"

UENUM(BlueprintType, Category = "Voxel")
enum class EBlockType : uint8
{
	None = 0,
	Grass,
	Dirt,
	Water,
};
