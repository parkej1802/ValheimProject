// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "S_Craftable.generated.h"


USTRUCT(BlueprintType)


struct FCraftableStruct : public FTableRowBase {

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AItem* Item;




};