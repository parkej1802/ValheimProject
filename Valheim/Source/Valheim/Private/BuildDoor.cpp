// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildDoor.h"

ABuildDoor::ABuildDoor()
{
	PrimaryActorTick.bCanEverTick = true;

	SetBuildDoor();
	static ConstructorHelpers::FObjectFinder<UCurveFloat> CurveFinder(TEXT("/Game/UP/BuildingMaterial/BuildTimeline/DoorTimeline.DoorTimeline"));
	if (CurveFinder.Succeeded())
	{
		DoorCurve = CurveFinder.Object;
	}
}

void ABuildDoor::BeginPlay()
{
	Super::BeginPlay();

	if (DoorCurve != nullptr) {
		// GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("BuildDoor curve Valid!"));
	}
	else {
		// GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("BuildDoor curve Failed"));
	}

	GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);

	DefaultRotation = GetStaticMeshComponent()->GetComponentRotation();

	FOnTimelineFloat ProgressUpdate;
	ProgressUpdate.BindUFunction(this, FName("UpdateDoorRotation"));

	FOnTimelineEvent FinishedEvent;
	FinishedEvent.BindUFunction(this, FName("FinishedDoorRotation"));

	DoorTimeline.AddInterpFloat(DoorCurve, ProgressUpdate);
	DoorTimeline.SetTimelineFinishedFunc(FinishedEvent);
}


void ABuildDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DoorTimeline.TickTimeline(DeltaTime);
}

void ABuildDoor::SetBuildDoor()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/UP/BuildingMaterial/Build/door.door'"));
	if (MeshAsset.Succeeded())
	{
		GetStaticMeshComponent()->SetStaticMesh(MeshAsset.Object);
	}
}

void ABuildDoor::UpdateDoorRotation(float value)
{
	IsOpening = true;
	FRotator NewRotation = DefaultRotation;
	NewRotation.Yaw += value;
	GetStaticMeshComponent()->SetWorldRotation(NewRotation);
}

void ABuildDoor::FinishedDoorRotation()
{
	IsOpening = false;
}

void ABuildDoor::InteractWithBuild_Implementation()
{

	if (!IsOpening) {
		if (!IsOpen) {
			IsOpen = true;
			DoorTimeline.Play();

		}
		else {
			IsOpen = false;
			DoorTimeline.Reverse();
		}
	}
}

void ABuildDoor::SetMesh_Implementation(UStaticMesh* Mesh)
{
	if (Mesh) {
		this->GetStaticMeshComponent()->SetStaticMesh(Mesh);
	}
}
