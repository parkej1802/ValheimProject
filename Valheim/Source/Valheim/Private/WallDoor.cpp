// Fill out your copyright notice in the Description page of Project Settings.


#include "WallDoor.h"

AWallDoor::AWallDoor()
{

	SetBuildWallDoor();

}
void AWallDoor::SetBuildWallDoor()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/UP/BuildingMaterial/Build/wall_door.wall_door'"));
	if (MeshAsset.Succeeded())
	{
		GetStaticMeshComponent()->SetStaticMesh(MeshAsset.Object);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed"));
	}
}
