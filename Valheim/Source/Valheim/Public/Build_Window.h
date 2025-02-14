// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "BuildInterface.h"
#include "Build_Window.generated.h"

/**
 * 
 */
UCLASS()
class VALHEIM_API ABuild_Window : public AStaticMeshActor, public IBuildInterface
{
	GENERATED_BODY()

public:
	ABuild_Window();

	void SetBuildWindow();
	
};
