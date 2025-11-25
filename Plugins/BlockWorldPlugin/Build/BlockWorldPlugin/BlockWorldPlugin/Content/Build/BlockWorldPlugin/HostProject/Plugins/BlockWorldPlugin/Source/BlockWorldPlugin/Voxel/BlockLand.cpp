// Created by y1. All Rights Reserved.


#include "BlockLand.h"

#include "Components/InstancedStaticMeshComponent.h"

#include "BlockLandDataAsset.h"
#include "BlockData.h"
#include "BlockRegistry.h"

ABlockLand::ABlockLand()
{
	PrimaryActorTick.bCanEverTick = false;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
}

void ABlockLand::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	GenerateLandFromData();
}


void ABlockLand::BeginDestroy()
{
	Super::BeginDestroy();
	ClearMeshInstances();
}

void ABlockLand::ClearMeshInstances()
{
	for (auto& Pair : MeshInstances)
	{
		if (Pair.Value)
		{
			Pair.Value->ClearInstances();
			Pair.Value->DestroyComponent();
		}
	}
}


void ABlockLand::GenerateLandFromData()
{
	if (!LandData || !BlockRegistry)
	{
		return;
	}

	if (!bEroded)
	{
		// Get a clone of the land data
		// So that every instance of it will have different randomized shape
		LandDataClone = DuplicateObject<UBlockLandDataAsset>(LandData, this);
		LandDataClone->RandomlyErodeEdges();
		bEroded = true;
	}

	for (int32 y = 0; y < LandDataClone->SizeY; ++y)
	{
		for (int32 x = 0; x < LandDataClone->SizeX; ++x)
		{
			const FBlock block = LandDataClone->GetBlock(x, y);

			if (block.Type == EBlockType::None)
			{
				continue;
			}

			const UBlockData* BlockData = BlockRegistry->GetData(block.Type);
			if (BlockData == nullptr)
			{
				continue;
			}


			UStaticMesh* Mesh = BlockRegistry->GetMesh();
			UMaterialInterface* Material = BlockData->GetMaterial();

			if (Material == nullptr || Mesh == nullptr)
			{
				continue;
			}

			FName Key = MakeMeshKey(Mesh, Material);
			UInstancedStaticMeshComponent* ISM = nullptr;

			if (MeshInstances.Contains(Key))
			{
				ISM = MeshInstances[Key];
			}
			else
			{
				ISM = NewObject<UInstancedStaticMeshComponent>(this);
				ISM->RegisterComponent();
				ISM->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
				ISM->SetStaticMesh(Mesh);
				ISM->SetMaterial(0, Material);
				ISM->SetMobility(EComponentMobility::Static);
				ISM->SetCastShadow(false);
				MeshInstances.Add(Key, ISM);
			}

			FVector Position = FVector(x * 100.0f, y * 100.0f, 100.0f);
			ISM->AddInstance(FTransform(Position));
		}
	}
}

FName ABlockLand::MakeMeshKey(const UStaticMesh* Mesh, const UMaterialInterface* Material)
{
	return FName(Mesh->GetName() + "_" + Material->GetName());
}
