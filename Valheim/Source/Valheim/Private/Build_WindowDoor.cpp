// Fill out your copyright notice in the Description page of Project Settings.


#include "Build_WindowDoor.h"

ABuild_WindowDoor::ABuild_WindowDoor()
{

	SetBuildWindowWall();
}

void ABuild_WindowDoor::SetBuildWindowWall()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/UP/BuildingMaterial/Build/wall_window.wall_window'"));
	if (MeshAsset.Succeeded())
	{
		GetStaticMeshComponent()->SetStaticMesh(MeshAsset.Object);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed"));
	}
}


