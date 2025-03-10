// Fill out your copyright notice in the Description page of Project Settings.


#include "Build_WindowDoor.h"

ABuild_WindowDoor::ABuild_WindowDoor()
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
	BoxComp3->SetCollisionProfileName(TEXT("FloorTace"));

	BoxComp4 = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp4"));
	BoxComp4->SetupAttachment(RootComponent);
	BoxComp4->SetRelativeLocation(FVector(0.0f, -200.0f, 400.0f));
	BoxComp4->SetBoxExtent(FVector(200.0f, 200.0f, 10.0f));
	BoxComp4->SetCollisionProfileName(TEXT("FloorTrace"));

	WindowBoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("WindowBoxComp"));
	WindowBoxComp->SetupAttachment(RootComponent);
	WindowBoxComp->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 131.0f), FRotator(0.0f, 90.0f, 0.0f));
	WindowBoxComp->SetBoxExtent(FVector(0.0f, 100.0f, 135.0f));
	WindowBoxComp->SetCollisionProfileName(TEXT("WindowTrace"));

	BoxCompArray.Push(BoxComp1);
	BoxCompArray.Push(BoxComp2);
	BoxCompArray.Push(BoxComp3);
	BoxCompArray.Push(BoxComp4);
	BoxCompArray.Push(WindowBoxComp);

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

void ABuild_WindowDoor::SetMesh_Implementation(UStaticMesh* Mesh)
{
	if (Mesh) {
		this->GetStaticMeshComponent()->SetStaticMesh(Mesh);
	}
}

TArray<UBoxComponent*> ABuild_WindowDoor::GetBoxCollision_Implementation()
{
	return BoxCompArray;
}

