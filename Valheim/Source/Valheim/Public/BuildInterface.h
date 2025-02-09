// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "BuildInterface.generated.h"

UINTERFACE(Blueprintable)
class UBuildInterface : public UInterface
{
    GENERATED_BODY()
};

class IBuildInterface
{
    GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Build")
	TArray<UBoxComponent*> GetBoxCollision();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Build")
	void SetMesh(UStaticMesh* Mesh);
};