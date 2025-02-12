// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlot.h"
#include "InventoryUI.h"

void UInventorySlot::NativeConstruct()
{
	Super::NativeConstruct();

	ItemImage->SetBrushFromTexture(Item.Thumbnail);

	ItemQuantity->SetText(FText::AsNumber(Item.Quantity));

	if (Item.Quantity > 1) {
		ItemQuantity->SetVisibility(ESlateVisibility::Visible);
	}
	else {
		ItemQuantity->SetVisibility(ESlateVisibility::Hidden);
	}

	if (ItemButton)
	{
		ItemButton->OnClicked.AddDynamic(this, &UInventorySlot::OnItemButtonClicked);
	}
}

void UInventorySlot::OnItemButtonClicked()
{
	APlayerController* PlayerController = GetOwningPlayer();
	if (PlayerController)
	{
		APawn* PlayerPawn = PlayerController->GetPawn();
		if (PlayerPawn)
		{
			AItem* SpawnedItem = GetWorld()->SpawnActor<AItem>(AItem::StaticClass(), PlayerPawn->GetActorTransform());
			InventoryComp->ItemsInInventory[Index] = FInventoryStruct();
			InventoryUI->LoadInventory(InventoryComp);
		}
	}
}	
