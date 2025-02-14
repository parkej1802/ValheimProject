// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemType.generated.h"
/**
 * 
 */

 UENUM(BlueprintType)
 enum class EItemType : uint8
 {
	Weapon		UMETA(DisplayName = "Weapon"),
	Material	UMETA(DisplayName = "Material")
 };