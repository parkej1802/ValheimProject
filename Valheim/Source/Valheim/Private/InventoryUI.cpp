// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryUI.h"
#include "AC_InventoryComponent.h"

void UInventoryUI::NativeConstruct()
{
	Super::NativeConstruct();
}

void UInventoryUI::LoadInventory(UAC_InventoryComponent* IC)
{
	InventoryWrapBox->ClearChildren();

    for (int32 i = 0; i < IC->ItemsInInventory.Num(); i++) {
        FInventoryStruct Item = IC->ItemsInInventory[i];

		if (InventorySlotWidget)
		{
			InventorySlotUI = CreateWidget<UInventorySlot>(GetWorld(), InventorySlotWidget);
			InventorySlotUI->Item = Item;
		}

		if (InventorySlotUI)
		{
			
			InventorySlotUI->InventoryComp = IC;
			InventorySlotUI->Index = i;

			InventoryWrapBox->AddChildToWrapBox(InventorySlotUI);
			InventorySlotUI->AddToViewport();
		}
    }
}
