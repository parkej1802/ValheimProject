// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Components/BoxComponent.h"
#include "BuildInterface.h"
#include "Build_Floor.generated.h"

/**
 * 
 */
UCLASS()
class VALHEIM_API ABuild_Floor : public AStaticMeshActor, public IBuildInterface
{
	GENERATED_BODY()

public:
	ABuild_Floor();

	void SetBuildFloorMesh();

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	class UBoxComponent* BoxComp1;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	class UBoxComponent* BoxComp2;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	class UBoxComponent* BoxComp3;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	class UBoxComponent* BoxComp4;

	TArray<UBoxComponent*> BoxCompArray;

	virtual TArray<UBoxComponent*> GetBoxCollision_Implementation() override;


};
