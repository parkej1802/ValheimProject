// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "WallDoor.generated.h"

/**
 * 
 */
UCLASS()
class VALHEIM_API AWallDoor : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:
	AWallDoor();
	void SetBuildWallDoor();
};
