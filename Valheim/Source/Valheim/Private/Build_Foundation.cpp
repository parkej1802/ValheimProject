#include "Build_Foundation.h"

ABuild_Foundation::ABuild_Foundation()
{

	BoxComp1 = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp1"));
	BoxComp1->SetupAttachment(RootComponent);
	BoxComp1->SetRelativeLocation(FVector(-400.0f, 0.0f, 0.0f));
	BoxComp1->SetBoxExtent(FVector(200.0f, 200.0f, 100.0f));
	BoxComp1->SetCollisionProfileName(TEXT("FoundationTrace"));

	BoxComp2 = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp2"));
	BoxComp2->SetupAttachment(RootComponent);
	BoxComp2->SetRelativeLocation(FVector(400.0f, 0.0f, 0.0f));
	BoxComp2->SetBoxExtent(FVector(200.0f, 200.0f, 100.0f));
	BoxComp2->SetCollisionProfileName(TEXT("FoundationTrace"));

	BoxComp3 = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp3"));
	BoxComp3->SetupAttachment(RootComponent);
	BoxComp3->SetRelativeLocation(FVector(0.0f, -400.0f, 0.0f));
	BoxComp3->SetBoxExtent(FVector(200.0f, 200.0f, 100.0f));
	BoxComp3->SetCollisionProfileName(TEXT("FoundationTrace"));

	BoxComp4 = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp4"));
	BoxComp4->SetupAttachment(RootComponent);
	BoxComp4->SetRelativeLocation(FVector(0.0f, 400.0f, 0.0f));
	BoxComp4->SetBoxExtent(FVector(200.0f, 200.0f, 100.0f));
	BoxComp4->SetCollisionProfileName(TEXT("FoundationTrace"));

	Wall1 = CreateDefaultSubobject<UBoxComponent>(TEXT("Wall1"));
	Wall1->SetupAttachment(RootComponent);
	Wall1->SetRelativeLocation(FVector(-200.0f, 0.0f, 113.0f));
	Wall1->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	Wall1->SetBoxExtent(FVector(200.0f, 32.0f, 200.0f));
	Wall1->SetCollisionProfileName(TEXT("WallTrace"));

	Wall2 = CreateDefaultSubobject<UBoxComponent>(TEXT("Wall2"));
	Wall2->SetupAttachment(RootComponent);
	Wall2->SetRelativeLocation(FVector(200.0f, 0.0f, 113.0f));
	Wall2->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	Wall2->SetBoxExtent(FVector(200.0f, 32.0f, 200.0f));
	Wall2->SetCollisionProfileName(TEXT("WallTrace"));

	Wall3 = CreateDefaultSubobject<UBoxComponent>(TEXT("Wall3"));
	Wall3->SetupAttachment(RootComponent);
	Wall3->SetRelativeLocation(FVector(0.0f, 200.0f, 113.0f));
	Wall3->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	Wall3->SetBoxExtent(FVector(200.0f, 32.0f, 200.0f));
	Wall3->SetCollisionProfileName(TEXT("WallTrace"));

	Wall4 = CreateDefaultSubobject<UBoxComponent>(TEXT("Wall4"));
	Wall4->SetupAttachment(RootComponent);
	Wall4->SetRelativeLocation(FVector(0.0f, -200.0f, 113.0f));
	Wall4->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	Wall4->SetBoxExtent(FVector(200.0f, 32.0f, 200.0f));
	Wall4->SetCollisionProfileName(TEXT("WallTrace"));

	
	BoxCompArray.Push(BoxComp1);
	BoxCompArray.Push(BoxComp2);
	BoxCompArray.Push(BoxComp3);
	BoxCompArray.Push(BoxComp4);
	BoxCompArray.Push(Wall1);
	BoxCompArray.Push(Wall2);
	BoxCompArray.Push(Wall3);
	BoxCompArray.Push(Wall4);

	SetFoundationMesh();
}

void ABuild_Foundation::SetFoundationMesh()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/UP/BuildingMaterial/Build/foundation_extention.foundation_extention'"));
	if (MeshAsset.Succeeded())
	{
		GetStaticMeshComponent()->SetStaticMesh(MeshAsset.Object);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed"));
	}
}

TArray<UBoxComponent*> ABuild_Foundation::GetBoxCollision_Implementation()
{
	//UE_LOG(LogTemp, Warning, TEXT("GetBoxCollision_Implementation FOUNDATION Working!"));

	return BoxCompArray;
}
