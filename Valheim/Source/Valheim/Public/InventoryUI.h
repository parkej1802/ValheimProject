// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/Overlay.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/WrapBox.h"
#include "InventorySlot.h"

class UAC_InventoryComponent;

#include "InventoryUI.generated.h"

/**
 * 
 */
UCLASS()
class VALHEIM_API UInventoryUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UCanvasPanel* InventoryCanvas;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UOverlay* InventoryOverlay;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UBorder* InventoryBorder;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* InventoryImage;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UWrapBox* InventoryWrapBox;

	virtual void NativeConstruct() override;

	void LoadInventory(UAC_InventoryComponent* IC);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> InventorySlotWidget;

	class UInventorySlot* InventorySlotUI;
};
