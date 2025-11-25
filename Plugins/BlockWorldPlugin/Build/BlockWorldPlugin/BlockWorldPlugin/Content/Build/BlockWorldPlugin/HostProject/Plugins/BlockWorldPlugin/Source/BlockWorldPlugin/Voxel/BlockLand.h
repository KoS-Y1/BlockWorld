// Created by y1. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "BlockLand.generated.h"

class UBlockRegistry;
class UBlockLandDataAsset;

UCLASS()
class BLOCKWORLDPLUGIN_API ABlockLand : public AActor
{
	GENERATED_BODY()
public:
	ABlockLand();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginDestroy() override;

private:
	UPROPERTY(EditAnywhere, Category = "Block Land")
	UBlockLandDataAsset* LandData;

	UPROPERTY(EditAnywhere, Category = "Block Land")
	UBlockRegistry *BlockRegistry;

	TMap<FName, UInstancedStaticMeshComponent*> MeshInstances;

	// TODO: use Store the randomized result in a non-construction-time method, like BeginPlay to make this safe
	// Currently it's only for editor testing
	UPROPERTY(Transient)
	bool bEroded = false;
	
	UBlockLandDataAsset* LandDataClone;
	
	void ClearMeshInstances();
	
	void GenerateLandFromData();
	
	static FName MakeMeshKey(const UStaticMesh* Mesh, const UMaterialInterface* Material);
};
