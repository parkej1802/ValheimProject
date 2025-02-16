// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySlot.h"
#include "InventoryUI.h"
#include "ValheimPlayer.h"

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
			if (InventoryComp) {
				Item = InventoryComp->ItemsInInventory[Index];
				InventoryComp->ItemsInInventory[Index] = FInventoryStruct();
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("InventoryComp in inventorySlot"));

				FVector SpawnLocation = PlayerPawn->GetActorLocation() + FVector(50.0f, 0.0f, 0.0f);
				FTransform SpawnTransform = PlayerPawn->GetActorTransform();
				SpawnTransform.SetLocation(SpawnLocation);

				AItem* SpawnedItem = GetWorld()->SpawnActor<AItem>(ItemClass, SpawnTransform);
				if (SpawnedItem) {
					// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Item Spawn in inventorySlot!"));
					SpawnedItem->SetItemData(Item);
				}
			}
			if (InventoryWidget)
			{
				InventoryUI = CreateWidget<UInventoryUI>(GetWorld(), InventoryWidget);
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("InventoryWidget in inventorySlot"));
			}
			if (InventoryUI)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("InventoryUI in inventorySlot"));
				//PlayerPawn->InventoryUI->RemoveFromParent();
				InventoryUI->LoadInventory(InventoryComp);
				//InventoryUI->AddToViewport();
				
			}
		}
	}
}	
