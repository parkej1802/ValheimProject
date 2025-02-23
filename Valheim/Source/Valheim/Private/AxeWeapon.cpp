// Fill out your copyright notice in the Description page of Project Settings.


#include "AxeWeapon.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Components/SphereComponent.h"
#include "EnermyTroll.h"


// Sets default values
AAxeWeapon::AAxeWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	
	//AxeComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AxeComp"));
	// AxeComp->SetupAttachment(CollisionComp);
	// AxeComp->SetRelativeLocationAndRotation(FVector(-14, 30, 100), FRotator(100, 0, 0));
	//AxeComp->SetRelativeScale3D(FVector(1));

	ConstructorHelpers::FObjectFinder<UStaticMesh>TempAxeMesh(TEXT("/Script/Engine.StaticMesh'/Game/Fab/Megascans/3D/Axe_ueqgcaifa/Medium/ueqgcaifa_tier_2.ueqgcaifa_tier_2'"));
	
	collisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	collisionComp->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	// 충돌체 크기 설정
	collisionComp->SetSphereRadius(20);
	collisionComp->SetGenerateOverlapEvents(true);
	RootComponent = collisionComp;
	AxeComp->OnComponentBeginOverlap;

	collisionComp->OnComponentBeginOverlap.AddDynamic(this, &AAxeWeapon::OnOverlapBegin);

}

// Called when the game starts or when spawned
void AAxeWeapon::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AAxeWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAxeWeapon::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEnermyTroll* enermy = Cast<AEnermyTroll>(OtherActor);
	if (enermy != nullptr)
	{
		OtherActor->Destroy();
	}

}

