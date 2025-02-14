// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemType.h"
#include "Components/StaticMeshComponent.h"
#include "S_Inventory.h"
#include "MasterItem.generated.h"

UCLASS()
class VALHEIM_API AMasterItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMasterItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, Category = RootScene)
	class USceneComponent* RootScene;

	UPROPERTY(EditAnywhere, Category = RootScene)
	class UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RootScene)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RootScene)
	EItemType Category;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RootScene)
	int32 Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RootScene)
	FText Description;

	//FInventoryStruct GetItemData();
};
