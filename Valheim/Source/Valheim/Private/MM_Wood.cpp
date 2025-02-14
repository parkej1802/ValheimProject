// Fill out your copyright notice in the Description page of Project Settings.


#include "MM_Wood.h"

AMM_Wood::AMM_Wood()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/Fab/Megascans/3D/Wood_Debris_Pack_vdqidbfiw/Medium/vdqidbfiw_LOD0_TIER2_001.vdqidbfiw_LOD0_TIER2_001'"));
	if (MeshAsset.Succeeded())
	{
		MeshComp->SetStaticMesh(MeshAsset.Object);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed"));
	}
}
