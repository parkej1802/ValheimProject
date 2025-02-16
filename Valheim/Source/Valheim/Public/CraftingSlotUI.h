// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "S_Craftable.h"
#include "Components/SizeBox.h"
#include "Components/Overlay.h"
#include "Components/Border.h"
#include "Components/WrapBox.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

#include "CraftingSlotUI.generated.h"

/**
 * 
 */
UCLASS()
class VALHEIM_API UCraftingSlotUI : public UUserWidget
{
	GENERATED_BODY()

public:


	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class USizeBox* CraftSlotSizeBox;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UOverlay* CraftSlotOverlay;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UBorder* CraftSlotBorder;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UImage* CraftSlotImage;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* CraftSlotButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UWrapBox* CraftSlotWrapBox;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* CraftSlotName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), meta = (ExposeOnSpawn = "true"))
	FCraftableStruct CraftItem;


	virtual void NativeConstruct() override;

};
