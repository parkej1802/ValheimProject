// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildDoor.h"

ABuildDoor::ABuildDoor()
{
	SetBuildDoor();
}

void ABuildDoor::SetBuildDoor()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/UP/BuildingMaterial/Build/door.door'"));
	if (MeshAsset.Succeeded())
	{
		GetStaticMeshComponent()->SetStaticMesh(MeshAsset.Object);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed"));
	}
}

void ABuildDoor::SetMesh_Implementation(UStaticMesh* Mesh)
{
	if (Mesh) {
		this->GetStaticMeshComponent()->SetStaticMesh(Mesh);
	}
}
