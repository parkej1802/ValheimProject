// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterItem.h"

// Sets default values
AMasterItem::AMasterItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	SetRootComponent(RootScene);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMasterItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMasterItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FInventoryStruct AMasterItem::GetItemData()
{
	FInventoryStruct Item;
	Item.Name = Name;
	Item.Value = Value;
	Item.Description = Description;
	Item.Category = Category;

	return Item;

}

