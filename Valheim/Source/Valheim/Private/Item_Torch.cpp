// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_Torch.h"
#include "Components/SceneComponent.h"


AItem_Torch::AItem_Torch()
{
	PrimaryActorTick.bCanEverTick = false;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TorchMesh"));
	RootComponent = MeshComp;

	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("TorchLight"));
	PointLight->SetupAttachment(MeshComp);
	PointLight->SetIntensity(300.0f);
	PointLight->SetLightColor(FLinearColor(1.0f, 0.6f, 0.2f));
	PointLight->SetAttenuationRadius(500.0f);
	PointLight->SetCastShadows(true);
	PointLight->bUseInverseSquaredFalloff = false;

	TexturePath = TEXT("/Script/Engine.Texture2D'/Game/Fab/torch-stick/source/torch-thumbnail.torch-thumbnail'");
	MeshPath = TEXT("/Script/Engine.StaticMesh'/Game/Fab/torch-stick/source/Torch.Torch'");

	UTexture2D* LoadedTexture = Cast<UTexture2D>(TexturePath.TryLoad());
	UStaticMesh* LoadedMesh = Cast<UStaticMesh>(MeshPath.TryLoad());

	if (LoadedMesh)
	{
		MeshComp->SetStaticMesh(LoadedMesh);
	}

	FInventoryStruct TorchItem;
	TorchItem.Name = FText::FromString("Torch");
	TorchItem.Value = 0;
	TorchItem.Description = FText::FromString("Fire!");
	TorchItem.Category = EItemType::Material;
	TorchItem.Stackable = false;
	TorchItem.Quantity = 1;
	TorchItem.Thumbnail = LoadedTexture;
	TorchItem.Mesh = LoadedMesh;
	TorchItem.ItemClass = AItem_Torch::StaticClass();

	SetItemData(TorchItem);
}


void AItem_Torch::BeginPlay()
{
	Super::BeginPlay();

	/*GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Torch spawned successfully!"));
	if (!PointLight)
	{
		PointLight = NewObject<UPointLightComponent>(this, UPointLightComponent::StaticClass());
		PointLight->SetupAttachment(MeshComp);
		PointLight->RegisterComponent();
	}

	PointLight->SetVisibility(true);
	PointLight->SetIntensity(300.0f);
	PointLight->SetLightColor(FLinearColor(1.0f, 0.6f, 0.2f));
	PointLight->SetAttenuationRadius(500.0f);
	PointLight->SetCastShadows(true);*/
}