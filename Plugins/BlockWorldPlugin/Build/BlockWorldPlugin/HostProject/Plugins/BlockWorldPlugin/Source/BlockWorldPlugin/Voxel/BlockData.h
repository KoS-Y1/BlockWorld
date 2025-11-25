// Created by y1. All Rights Reserved.


#pragma once

#include "CoreMinimal.h"

#include "BlockData.generated.h"

UCLASS(BlueprintType)
class BLOCKWORLDPLUGIN_API UBlockData : public UDataAsset
{
	GENERATED_BODY()

public:
	[[nodiscard]] UMaterialInterface* GetMaterial() const { return Material; }

private:
	UPROPERTY(EditAnywhere)
	UMaterialInterface* Material;
};
