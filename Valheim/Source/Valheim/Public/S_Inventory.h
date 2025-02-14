// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemType.h"
#include "Engine/Texture2D.h"
#include "Engine/StaticMesh.h"

#include "S_Inventory.generated.h"

USTRUCT(BlueprintType)

struct FInventoryStruct : public FTableRowBase {

	GENERATED_BODY()

	// Different Tutorial
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemType Category;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Stackable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Quantity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Thumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMesh* Mesh;

	FInventoryStruct()
		: Name(FText::FromString(TEXT("")))
		, Value(0)
		, Description(FText::FromString(TEXT("")))
		, Category(EItemType::Material) 
		, Stackable(false)
		, Quantity(0)
		, Thumbnail(nullptr)
		, Mesh(nullptr)
	{
	}

	FInventoryStruct(FText InName, int32 InValue, FText InDescription, EItemType InCategory, bool bStackable, int32 InQuantity, UTexture2D* InThumbnail, UStaticMesh* InMesh)
		: Name(InName)
		, Value(InValue)
		, Description(InDescription)
		, Category(InCategory)
		, Stackable(bStackable)
		, Quantity(InQuantity)
		, Thumbnail(InThumbnail)
		, Mesh(InMesh)
	{
	}
};
