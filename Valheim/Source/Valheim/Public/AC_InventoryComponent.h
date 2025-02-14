// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Camera/CameraComponent.h"
#include "MasterItem.h"
#include "S_Inventory.h"
#include "Item.h"

class AValheimPlayer;
class UInventoryUI;

#include "AC_InventoryComponent.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VALHEIM_API UAC_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAC_InventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(EditAnywhere)
	class AValheimPlayer* ConnectedActor;

	void DetectPlayer();
	void TryAddItem(AActor* Actor);
	
	FInventoryStruct ItemData;

	void IsItemAlreadyInInventory();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inventory)
	TArray<FInventoryStruct> ItemsInInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inventory)
	TSubclassOf<UUserWidget> InventoryWidget;

	class UInventoryUI* InventoryUI;

	void PickUpItem();


	
};
