// Fill out your copyright notice in the Description page of Project Settings.

#include "CraftingSlotUI.h"
#include "AC_CraftingComponent.h"
#include "CraftingUI.h"

void UCraftingSlotUI::NativeConstruct()
{
	Super::NativeConstruct();

	CraftSlotImage->SetBrushFromTexture(CraftItem.Thumbnail);

	if (CraftItem.NormalItemName != "None") {
		CraftSlotName->SetText(FText::FromName(CraftItem.NormalItemName));
	}
	else {
		CraftSlotName->SetText(FText::FromName(CraftItem.BuildItemName));
	}

	if (CraftSlotButton)
	{
		CraftSlotButton->OnClicked.AddDynamic(this, &UCraftingSlotUI::OnCraftItemButtonClicked);
	}
}

void UCraftingSlotUI::OnCraftItemButtonClicked()
{
	APlayerController* PlayerController = GetOwningPlayer();
	if (PlayerController)
	{
		APawn* PlayerPawn = PlayerController->GetPawn();
		if (PlayerPawn)
		{
			BuildComp = PlayerPawn->FindComponentByClass<UAC_BuildComponent>();
			if (CraftComp) {
				FName SlotName = FName(*CraftSlotName->GetText().ToString());
				CraftItem = CraftComp->CraftableDataMap[SlotName];
				if (!BuildComp)
				{
					//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("BuildComp is NULL!"));
					return;
				}
				BuildComp->LaunchBuildMode(SlotName);
				BuildComp->IsBuildMode = false;
				if (CraftUI) {
					CraftUI->RemoveFromParent();
				}
				FInputModeGameOnly GameInputMode;
				PlayerController->SetInputMode(GameInputMode);
				PlayerController->bShowMouseCursor = false;

			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("CraftItem not found!"));
			}
		}
	}

}

void UCraftingSlotUI::BuildMode()
{
	
}
