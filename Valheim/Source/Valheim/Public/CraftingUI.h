// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/Overlay.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/WrapBox.h"
#include "CraftingSlotUI.h"
#include "S_Craftable.h"

class UAC_CraftingComponent;

#include "CraftingUI.generated.h"

/**
 * 
 */
UCLASS()
class VALHEIM_API UCraftingUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UCanvasPanel* CraftingCanvasPanel;

	//UPROPERTY(EditAnywhere, meta = (BindWidget))
	//class UOverlay* CraftingOverlay;

	//UPROPERTY(EditAnywhere, meta = (BindWidget))
	//class UBorder* CraftingBorder;

	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* CraftingItemCategory;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* CraftingImage;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UWrapBox* CraftingItemContainer;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UHorizontalBox* CraftingHorizontalBox;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class USizeBox* SizeBox_All;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class USizeBox* SizeBox_Material;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class USizeBox* SizeBox_Weapon;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* Button_All;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* Button_Material;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* Button_Weapon;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* Text_All;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* Text_Material;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* Text_Weapon;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UVerticalBox* CraftingVerticalBox;


// Crafting Slot 
public:
	void LoadCraftInventory(UAC_CraftingComponent* CC);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> CraftSlotWidget;

	class UCraftingSlotUI* CSlotUI;
};
