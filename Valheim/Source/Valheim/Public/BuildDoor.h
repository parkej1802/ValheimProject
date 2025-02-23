// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "BuildInterface.h"
#include "Components/TimelineComponent.h"
#include "BuildDoor.generated.h"

class UCurveFloat;
/**
 * 
 */
UCLASS()
class VALHEIM_API ABuildDoor : public AStaticMeshActor, public IBuildInterface
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	ABuildDoor();

	void SetBuildDoor();

	virtual void SetMesh_Implementation(UStaticMesh* Mesh) override;

// Open Door
	virtual void InteractWithBuild_Implementation() override;
	FRotator DefaultRotation;

	bool IsOpen = false;
	bool IsOpening = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UCurveFloat* DoorCurve = nullptr;

	FTimeline DoorTimeline;

	UFUNCTION()
	void UpdateDoorRotation(float value);

	UFUNCTION()
	void FinishedDoorRotation();
};
