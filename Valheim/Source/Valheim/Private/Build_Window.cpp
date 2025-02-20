// Fill out your copyright notice in the Description page of Project Settings.


#include "Build_Window.h"

ABuild_Window::ABuild_Window()
{
	SetBuildWindow();
}

void ABuild_Window::SetBuildWindow()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/UP/BuildingMaterial/Build/window.window'"));
	if (MeshAsset.Succeeded())
	{
		GetStaticMeshComponent()->SetStaticMesh(MeshAsset.Object);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed"));
	}
}
