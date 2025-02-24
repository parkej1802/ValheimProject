// Fill out your copyright notice in the Description page of Project Settings.


#include "Tree.h"
#include "Item.h"
#include "Item_Material_Wood.h"

// Sets default values
ATree::ATree()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	SetRootComponent(SceneComp);

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetupAttachment(RootComponent);
	BoxComp->SetBoxExtent(FVector(50.f));

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ATree::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATree::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ATree::TakeDamage(float Damage)
{
	Health -= Damage;
	if (Health <= 0)
	{
		//MeshComp->SetSimulatePhysics(true);
		/*FVector ImpulseDirection = FVector(1.f, 0.f, 0.f);
		MeshComp->AddImpulse(ImpulseDirection * 5.f, NAME_None, true);*/

		FVector SpawnLocation = GetActorLocation() + FVector(0.f, 0.f, 100.f);
		FTransform SpawnTransform = GetActorTransform();
		SpawnTransform.SetLocation(SpawnLocation);

		TSubclassOf<AItem> ItemClass = AItem_Material_Wood::StaticClass();

		AItem* SpawnedItem = GetWorld()->SpawnActor<AItem>(ItemClass, SpawnTransform);
		
		Destroy();
	}
}

void ATree::ResetDamageState()
{
	HasTakenDamage = false;  
}