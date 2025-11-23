// Created by y1. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "BlockType.h"
#include "BlockData.h"

#include "BlockRegistry.generated.h"

UCLASS(BlueprintType)
class BLOCKWORLDPLUGIN_API UBlockRegistry : public UDataAsset
{
	GENERATED_BODY()

public:
	[[nodiscard]] const UBlockData* GetData(EBlockType) const;
	[[nodiscard]] UStaticMesh* GetMesh() const { return Mesh; }

private:
	UPROPERTY(EditDefaultsOnly)
	TMap<EBlockType, class UBlockData*> Blocks;

	UPROPERTY(EditDefaultsOnly)
	UStaticMesh* Mesh;
};
