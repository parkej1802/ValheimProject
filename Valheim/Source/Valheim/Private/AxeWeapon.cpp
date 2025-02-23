// Fill out your copyright notice in the Description page of Project Settings.


#include "AxeWeapon.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Components/SphereComponent.h"

// Sets default values
AAxeWeapon::AAxeWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*
	AxeComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AxeComp"));
	AxeComp->SetRelativeLocationAndRotation(FVector(-14, 30, 100), FRotator(100, 0, 0));
	AxeComp->SetRelativeScale3D(FVector(1));
	RootComponent = AxeComp;

	ConstructorHelpers::FObjectFinder<UStaticMesh>TempAxeMesh(TEXT("/Script/Engine.Texture2D'/Game/Fab/Megascans/3D/Axe_ueqgcaifa/Medium/axe.axe'"));
	*/
	collisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	collisionComp->SetCollisionProfileName(TEXT("BlockAll"));
	// 충돌체 크기 설정
	collisionComp->SetSphereRadius(13);
	RootComponent = collisionComp;
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

