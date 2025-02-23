// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "BuildInterface.h"
#include "Components/BoxComponent.h"
#include "Components/TimelineComponent.h"
#include "WallDoor.generated.h"

class UCurveFloat;
/**
 * 
 */
UCLASS()
class VALHEIM_API AWallDoor : public AStaticMeshActor, public IBuildInterface
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	AWallDoor();

	void SetBuildWallDoor();

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	class UBoxComponent* BoxComp1;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	class UBoxComponent* BoxComp2;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	class UBoxComponent* BoxComp3;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	class UBoxComponent* BoxComp4;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	class UBoxComponent* DoorBoxComp;


	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TArray<UBoxComponent*> BoxCompArray;


	virtual TArray<UBoxComponent*> GetBoxCollision_Implementation() override;

	virtual void SetMesh_Implementation(UStaticMesh* Mesh) override;


//// Door Opening
//	virtual void InteractWithBuild_Implementation() override;
//	FRotator DefaultRotation;
//
//	bool IsOpen = false;
//	bool IsOpening = false;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//    UCurveFloat* DoorCurve;
//
//	FTimeline DoorTimeline;
//
//	UFUNCTION()
//	void UpdateDoorRotation(float value);
//
//	UFUNCTION()
//	void FinishedDoorRotation();
};
