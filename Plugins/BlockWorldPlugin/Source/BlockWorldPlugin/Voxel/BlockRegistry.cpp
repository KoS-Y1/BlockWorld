// Created by y1. All Rights Reserved.


#include "BlockRegistry.h"

const UBlockData* UBlockRegistry::GetData(EBlockType Type) const
{
	if (Blocks.Contains(Type))
	{
		return Blocks[Type];
	}

	return nullptr;
}
