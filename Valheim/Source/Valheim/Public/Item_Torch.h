// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Components/PointLightComponent.h"
#include "Components/SceneComponent.h"
#include "Item_Torch.generated.h"

/**
 * 
 */
UCLASS()
class VALHEIM_API AItem_Torch : public AItem
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	AItem_Torch();

	FSoftObjectPath TexturePath;
	FSoftObjectPath MeshPath;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPointLightComponent* PointLight;

	int32 Health = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* TorchComp;
};
