// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Components/BoxComponent.h"
#include "BuildInterface.h"
#include "Build_WindowDoor.generated.h"

/**
 * 
 */
UCLASS()
class VALHEIM_API ABuild_WindowDoor : public AStaticMeshActor, public IBuildInterface
{
	GENERATED_BODY()

public:
	ABuild_WindowDoor();
	void SetBuildWindowWall();

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	class UBoxComponent* BoxComp1;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	class UBoxComponent* BoxComp2;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	class UBoxComponent* BoxComp3;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	class UBoxComponent* BoxComp4;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TArray<UBoxComponent*> BoxCompArray;


	virtual TArray<UBoxComponent*> GetBoxCollision_Implementation() override;

	virtual void SetMesh_Implementation(UStaticMesh* Mesh) override;
};
