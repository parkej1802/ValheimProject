// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ValheimPlayer.h"
#include "Engine/DataTable.h"
#include "S_Craftable.h"
#include "S_Buildables.h"
#include "CraftingUI.h"
#include "AC_CraftingComponent.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VALHEIM_API UAC_CraftingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAC_CraftingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CraftingSystem)
	AValheimPlayer* PlayerCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	UDataTable* CraftableDB;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	TArray<FName> RowNames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	TArray<FName> UnlockedItemNames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	TSet<FName> UnlockedSet;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data)
	TMap<FName, FCraftableStruct> CraftableDataMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, FBuildingStruct> BuildableDataMap;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Player)
	int PlayerLevel = 0;


public:

// Crafting Functions
	void InitCalculateCrafting();
	void GetDataTableRowNames();
	void CalculateUnlockedItem();
	void UpdateAllCraftingSlot();
	void StartSlotCreation();
	void CreateSlotWidget();
};
