// Fill out your copyright notice in the Description page of Project Settings.


#include "CraftingUI.h"
#include "AC_CraftingComponent.h"


void UCraftingUI::LoadCraftInventory(UAC_CraftingComponent* CC)
{

	CraftingItemContainer->ClearChildren();

	if (!CC)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Crafting Component NULL!"));
		return;
	}


	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("LoadCraftInventory"));

	for (TPair<FName, FCraftableStruct>& CraftPair : CC->CraftableDataMap)
	{
		FCraftableStruct& CraftItemData = CraftPair.Value;
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Craft Item is there"));
		if (CraftSlotWidget)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("CraftSlotWidget"));
			CSlotUI = CreateWidget<UCraftingSlotUI>(GetWorld(), CraftSlotWidget);
			if (CSlotUI)
			{
				CSlotUI->CraftComp = CC;
				CSlotUI->CraftUI = this;
				CSlotUI->CraftItem = CraftItemData;
				CraftingItemContainer->AddChild(CSlotUI);
				CSlotUI->AddToViewport();
			}
		}
	}
}


