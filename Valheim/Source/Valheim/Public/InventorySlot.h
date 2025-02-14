// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "S_Inventory.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/Overlay.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Item.h"
#include "AC_InventoryComponent.h"

class UInventoryUI;
#include "InventorySlot.generated.h"

/**
 * 
 */
UCLASS()
class VALHEIM_API UInventorySlot : public UUserWidget
{
	GENERATED_BODY()


public:

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class USizeBox* ItemSizeBox;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UOverlay* ItemOverlay;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* ItemButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* ItemImage;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* ItemQuantity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), meta = (ExposeOnSpawn = "true"))
	FInventoryStruct Item;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), meta = (ExposeOnSpawn = "true"))
	int32 Index;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	class UAC_InventoryComponent* InventoryComp;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	TSubclassOf<UUserWidget> InventoryWidget;

	class UInventoryUI* InventoryUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	class AItem* ItemData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
    TSubclassOf<AItem> ItemClass;

	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnItemButtonClicked();
};
