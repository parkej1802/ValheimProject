// Fill out your copyright notice in the Description page of Project Settings.


#include "WM_Axe.h"

AWM_Axe::AWM_Axe()
{
	

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/Fab/Megascans/3D/Axe_ueqgcaifa/Medium/ueqgcaifa_tier_2.ueqgcaifa_tier_2'"));
	if (MeshAsset.Succeeded())
	{
		MeshComp->SetStaticMesh(MeshAsset.Object);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed"));
	}
}
