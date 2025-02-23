// Fill out your copyright notice in the Description page of Project Settings.


#include "AC_CraftingComponent.h"

// Sets default values for this component's properties
UAC_CraftingComponent::UAC_CraftingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UAC_CraftingComponent::BeginPlay()
{
	Super::BeginPlay();


	AActor* Owner = GetOwner();

	if (Owner)
	{
		PlayerCharacter = Cast<AValheimPlayer>(Owner);

		FString DataTablePath = TEXT("/Script/Engine.DataTable'/Game/UP/CraftingSystem/CraftableDB.CraftableDB'");
		CraftableDB = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *DataTablePath));
		InitCalculateCrafting();
		
	}

	
}


// Called every frame
void UAC_CraftingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAC_CraftingComponent::InitCalculateCrafting()
{
	GetDataTableRowNames();
}

void UAC_CraftingComponent::GetDataTableRowNames()
{
	if (CraftableDB)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("CraftableDB is valid!"));
		RowNames = CraftableDB->GetRowNames();
		CalculateUnlockedItem();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Failed DB"));
	}
}

void UAC_CraftingComponent::CalculateUnlockedItem()
{
	for (FName& RowName : RowNames)
	{
		FCraftableStruct* RowData = CraftableDB->FindRow<FCraftableStruct>(RowName, TEXT("Context"));
		if (RowData->RequiredLevel <= PlayerLevel) {
			if (RowData) {
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("RowData1"));
				CraftableDataMap.Add(RowName, *RowData);
			}
		}
	}


}

void UAC_CraftingComponent::UpdateAllCraftingSlot()
{
	
}

void UAC_CraftingComponent::StartSlotCreation()
{

}