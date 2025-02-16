// Fill out your copyright notice in the Description page of Project Settings.


#include "CraftingSlotUI.h"

void UCraftingSlotUI::NativeConstruct()
{
	Super::NativeConstruct();

	CraftSlotImage->SetBrushFromTexture(CraftItem.Thumbnail);

	CraftSlotName->SetText(FText::FromName(CraftItem.NormalItemName));
}
