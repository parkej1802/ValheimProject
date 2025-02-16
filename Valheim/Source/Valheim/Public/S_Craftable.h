// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "S_Craftable.generated.h"


USTRUCT(BlueprintType)


struct FCraftableStruct : public FTableRowBase {

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AItem> Item;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> CraftBuildingItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<TSubclassOf<AItem>, int32> Ingredients;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName NormalItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName BuildItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int RequiredLevel = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CraftingTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Thumbnail;
};