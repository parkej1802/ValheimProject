// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "BuildInterface.h"
#include "BuildDoor.generated.h"

/**
 * 
 */
UCLASS()
class VALHEIM_API ABuildDoor : public AStaticMeshActor, public IBuildInterface
{
	GENERATED_BODY()


public:
	ABuildDoor();

	void SetBuildDoor();

	virtual void SetMesh_Implementation(UStaticMesh* Mesh) override;
};
