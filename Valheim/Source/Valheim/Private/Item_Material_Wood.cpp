// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_Material_Wood.h"

// Sets default values
AItem_Material_Wood::AItem_Material_Wood()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    TexturePath = TEXT("/Game/Fab/Megascans/3D/Wood_Debris_Pack_vdqidbfiw/Medium/Wood.Wood");
    MeshPath = TEXT("/Game/Fab/Megascans/3D/Wood_Debris_Pack_vdqidbfiw/Medium/vdqidbfiw_LOD0_TIER2_001.vdqidbfiw_LOD0_TIER2_001");

    UTexture2D* LoadedTexture = Cast<UTexture2D>(TexturePath.TryLoad());
    UStaticMesh* LoadedMesh = Cast<UStaticMesh>(MeshPath.TryLoad());

    FInventoryStruct WoodItem;
    WoodItem.Name = FText::FromString("Wood");
    WoodItem.Value = 20;
    WoodItem.Description = FText::FromString("Building Material");
    WoodItem.Category = EItemType::Material;
    WoodItem.Stackable = true;
    WoodItem.Quantity = 20;
    WoodItem.Thumbnail = LoadedTexture;
    WoodItem.Mesh = LoadedMesh;
    WoodItem.ItemClass = AItem_Material_Wood::StaticClass();

    SetItemData(WoodItem);
}

// Called when the game starts or when spawned
void AItem_Material_Wood::BeginPlay()
{
	Super::BeginPlay();

    
}

// Called every frame
void AItem_Material_Wood::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

