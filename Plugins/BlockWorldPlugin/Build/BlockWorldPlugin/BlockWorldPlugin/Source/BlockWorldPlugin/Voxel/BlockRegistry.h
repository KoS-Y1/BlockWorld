// Created by y1. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "BlockType.h"

#include "BlockRegistry.generated.h"

class UBlockData;

UCLASS(BlueprintType, Category = "Voxel")
class BLOCKWORLDPLUGIN_API UBlockRegistry : public UDataAsset
{
	GENERATED_BODY()

public:
	[[nodiscard]] const UBlockData* GetData(EBlockType) const;
	[[nodiscard]] UStaticMesh* GetMesh() const { return Mesh; }

private:
	UPROPERTY(EditDefaultsOnly, Category = "Voxel")
	TMap<EBlockType, class UBlockData*> Blocks;

	UPROPERTY(EditDefaultsOnly, Category = "Voxel")
	UStaticMesh* Mesh;
};
