// Fill out your copyright notice in the Description page of Project Settings.


#include "WallDoor.h"

AWallDoor::AWallDoor()
{
	BoxComp1 = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp1"));
	BoxComp1->SetupAttachment(RootComponent);
	BoxComp1->SetRelativeLocation(FVector(-400.0f, 0.0f, 0.0f));
	BoxComp1->SetBoxExtent(FVector(200.0f, 10.0f, 200.0f));
	BoxComp1->SetCollisionProfileName(TEXT("WallTrace"));

	BoxComp2 = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp2"));
	BoxComp2->SetupAttachment(RootComponent);
	BoxComp2->SetRelativeLocation(FVector(400.0f, 0.0f, 0.0f));
	BoxComp2->SetBoxExtent(FVector(200.0f, 10.0f, 200.0f));
	BoxComp2->SetCollisionProfileName(TEXT("WallTrace"));

	BoxComp3 = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp3"));
	BoxComp3->SetupAttachment(RootComponent);
	BoxComp3->SetRelativeLocation(FVector(0.0f, 200.0f, 400.0f));
	BoxComp3->SetBoxExtent(FVector(200.0f, 200.0f, 10.0f));
	BoxComp3->SetCollisionProfileName(TEXT("FloorTrace"));

	BoxComp4 = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp4"));
	BoxComp4->SetupAttachment(RootComponent);
	BoxComp4->SetRelativeLocation(FVector(0.0f, -200.0f, 400.0f));
	BoxComp4->SetBoxExtent(FVector(200.0f, 200.0f, 10.0f));
	BoxComp4->SetCollisionProfileName(TEXT("FloorTrace"));

	DoorBoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("DoorBoxComp"));
	DoorBoxComp->SetupAttachment(RootComponent);
	DoorBoxComp->SetRelativeLocationAndRotation(FVector(-64.0f, 0.0f, 11.0f), FRotator(0.0f, 90.0f, 0.0f));
	DoorBoxComp->SetBoxExtent(FVector(1.0f, 135.0f, 180.0f));
	DoorBoxComp->SetCollisionProfileName(TEXT("DoorTrace"));

	BoxCompArray.Push(BoxComp1);
	BoxCompArray.Push(BoxComp2);
	BoxCompArray.Push(BoxComp3);
	BoxCompArray.Push(BoxComp4);
	BoxCompArray.Push(DoorBoxComp);

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

void AWallDoor::SetMesh_Implementation(UStaticMesh* Mesh)
{
	if (Mesh) {
		this->GetStaticMeshComponent()->SetStaticMesh(Mesh);
	}
}

TArray<UBoxComponent*> AWallDoor::GetBoxCollision_Implementation()
{
	return BoxCompArray;
}
