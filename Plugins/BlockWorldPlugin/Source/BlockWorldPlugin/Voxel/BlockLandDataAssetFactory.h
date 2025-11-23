// Created by y1. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "BlockLandDataAsset.h"

#include "BlockLandDataAssetFactory.generated.h"

UCLASS(BlueprintType, EditInlineNew)
class BLOCKWORLDPLUGIN_API UBlockLandDataAssetFactory : public UFactory
{
	GENERATED_BODY()
public:
	UBlockLandDataAssetFactory()
	{
		bCreateNew = true;
		bEditAfterNew = true;
		SupportedClass = UBlockLandDataAsset::StaticClass();
	}

	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags,
									  UObject* Context, FFeedbackContext* Warn) override
	{
		return NewObject<UBlockLandDataAsset>(InParent, Class, Name, Flags);
	}
};
