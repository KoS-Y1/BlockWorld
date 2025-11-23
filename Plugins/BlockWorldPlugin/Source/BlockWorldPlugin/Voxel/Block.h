// Created by y1. All Rights Reserved.


#pragma once

#include "CoreMinimal.h"

#include "BlockType.h"

#include "Block.generated.h"

USTRUCT(BlueprintType)
struct BLOCKWORLDPLUGIN_API FBlock
{
	GENERATED_BODY()

	FBlock() : Type(EBlockType::None), bWalkable(false) {}

	UPROPERTY(EditAnywhere)
	EBlockType Type;
	
	UPROPERTY(EditAnywhere)
	bool bWalkable;
};
