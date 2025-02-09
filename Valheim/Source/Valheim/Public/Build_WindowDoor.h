// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Build_WindowDoor.generated.h"

/**
 * 
 */
UCLASS()
class VALHEIM_API ABuild_WindowDoor : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	ABuild_WindowDoor();
	void SetBuildWindowWall();
};
