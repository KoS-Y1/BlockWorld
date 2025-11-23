// Created by y1. All Rights Reserved.


#include "BlockLandDataAsset.h"

#include "Randomizer/Randomizer.h"
#include "UObject/FastReferenceCollector.h"

void UBlockLandDataAsset::SetBlock(int32 Idx, EBlockType Type, bool Walkable)
{
	if (!Blocks.IsValidIndex(Idx))
	{
		return;
	}
	Blocks[Idx].bWalkable = Walkable;
	Blocks[Idx].Type = Type;
}

void UBlockLandDataAsset::SetBlock(int32 X, int32 Y, EBlockType Type, bool Walkable)
{
	SetBlock(X + Y * SizeX, Type, Walkable);
}

EBlockType UBlockLandDataAsset::GetBlockType(int32 Idx) const
{
	if (!Blocks.IsValidIndex(Idx))
	{
		return EBlockType::None;
	}

	return Blocks[Idx].Type;
}

EBlockType UBlockLandDataAsset::GetBlockType(int32 X, int32 Y) const
{
	return GetBlockType(X + Y * SizeX);
}

FBlock UBlockLandDataAsset::GetBlock(int32 Idx) const
{
	if (Blocks.IsValidIndex(Idx))
	{
		return Blocks[Idx];
	}

	// Return an empty block
	return FBlock();
}

FBlock UBlockLandDataAsset::GetBlock(int32 X, int32 Y) const
{
	return GetBlock(X + Y * SizeX);
}

void UBlockLandDataAsset::RandomlyErodeEdges()
{
	float Probability = ErosionProbability;
	
	for (int32 Depth = 1; Depth <= ErosionDepth; Depth++)
	{
		// Gathering ring of blocks at depth
		TArray<FIntPoint> Ring;
		for (int32 Y = 0; Y < SizeY; Y++)
		{
			for (int32 X = 0; X < SizeX; X++)
			{
				bool bRing = (X == Depth - 1) || (X == SizeX - Depth) || (Y == Depth - 1) || (Y == SizeY - Depth);
				if (bRing)
				{
					Ring.Emplace(X, Y);
				}
			}
		}

		
		// Probablistic erosion
		for (auto& Block : Ring)
		{
			if (GetBlockType(Block.X, Block.Y) != EBlockType::None && IsAdjacentToNone(Block.X, Block.Y) &&
				URandomizer::GetInstance()->RandomFloat() < Probability)
			{
				SetBlock(Block.X, Block.Y, EBlockType::None, false);
			}
		}

		// Flood fill from all interior
		TArray<bool> Reachable;
		Reachable.Init(false, SizeX * SizeY);
		TQueue<FIntPoint> FloodQueue;

		// Inner blocks
		for (int32 Y = Depth; Y < SizeY - Depth; Y++)
		{
			for (int32 X = Depth; X < SizeX - Depth; X++)
			{
				if (GetBlockType(X, Y) != EBlockType::None)
				{
					int Idx = X + Y * SizeX;
					Reachable[Idx] = true;
					FloodQueue.Enqueue(FIntPoint(X, Y));
				}
			}
		}

		// Four direction flood
		const int32 DirectionX[4] = {-1, 1, 0, 0};
		const int32 DirectionY[4] = {0, 0, -1, 1};
		while (!FloodQueue.IsEmpty())
		{
			FIntPoint CurrentBlock;
			FloodQueue.Dequeue(CurrentBlock);

			for (int32 i = 0; i < 4; i++)
			{
				int32 X = CurrentBlock.X + DirectionX[i];
				int32 Y = CurrentBlock.Y + DirectionY[i];
				if (X < 0 || X >= SizeX || Y < 0 || Y >= SizeY)
				{
					continue;
				}

				int32 Idx = X + Y * SizeX;
				if (!Reachable[Idx] && GetBlockType(X, Y) != EBlockType::None)
				{
					Reachable[Idx] = true;
					FloodQueue.Enqueue(FIntPoint(X, Y));
				}
			}
		}

		// Erode not flooded blocks
		for (int32 Idx = 0; Idx < Blocks.Num(); Idx++)
		{
			if (!Reachable[Idx])
			{
				SetBlock(Idx, EBlockType::None, false);
			}
		}

		Probability -= 0.2f;

	}
}

bool UBlockLandDataAsset::IsAdjacentToNone(int32 X, int32 Y) const
{
	// Up
	if (GetBlockType(X, Y - 1) == EBlockType::None)
	{
		return true;
	}
	// Down
	if (GetBlockType(X, Y + 1) == EBlockType::None)
	{
		return true;
	}
	// Left
	if (GetBlockType(X - 1, Y) == EBlockType::None)
	{
		return true;
	}
	// Right
	if (GetBlockType(X + 1, Y) == EBlockType::None)
	{
		return true;
	}

	return false;
}

bool UBlockLandDataAsset::IsAdjacentToNone(int32 Idx) const
{
	int32 X = Idx % SizeX;
	int32 Y = Idx / SizeX;

	return IsAdjacentToNone(X, Y);
}
