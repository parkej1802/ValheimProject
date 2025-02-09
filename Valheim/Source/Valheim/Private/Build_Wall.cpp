// Fill out your copyright notice in the Description page of Project Settings.


#include "Build_Wall.h"

ABuild_Wall::ABuild_Wall()
{
	BoxComp1 = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp1"));
	BoxComp1->SetupAttachment(RootComponent);
	BoxComp1->SetRelativeLocation(FVector(-400.0f, 0.0f, 0.0f));
	BoxComp1->SetBoxExtent(FVector(200.0f, 200.0f, 100.0f));
	BoxComp1->SetCollisionProfileName(TEXT("WallTrace"));

	BoxComp2 = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp2"));
	BoxComp2->SetupAttachment(RootComponent);
	BoxComp2->SetRelativeLocation(FVector(400.0f, 0.0f, 0.0f));
	BoxComp2->SetBoxExtent(FVector(200.0f, 200.0f, 100.0f));
	BoxComp2->SetCollisionProfileName(TEXT("WallTrace"));

	BoxCompArray.Push(BoxComp1);
	BoxCompArray.Push(BoxComp2);

	SetBuildWallMesh();
}

void ABuild_Wall::SetBuildWallMesh()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/UP/BuildingMaterial/Build/wall.wall'"));
	if (MeshAsset.Succeeded())
	{
		GetStaticMeshComponent()->SetStaticMesh(MeshAsset.Object);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed"));
	}
}

void ABuild_Wall::SetMesh_Implementation(UStaticMesh* Mesh)
{
	if (Mesh) {
		this->GetStaticMeshComponent()->SetStaticMesh(Mesh);
	}
}

TArray<UBoxComponent*> ABuild_Wall::GetBoxCollision_Implementation()
{
	//UE_LOG(LogTemp, Warning, TEXT("GetBoxCollision_Implementation WALL Working!"));

	return BoxCompArray;
}
