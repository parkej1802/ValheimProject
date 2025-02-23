// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "PlayerMainWidget.generated.h"

/**
 * 
 */
UCLASS()
class VALHEIM_API UPlayerMainWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY()
	class AValheimPlayer* PlayerCharacter;

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;
// 체력

	UPROPERTY(EditAnywhere, meta = (BindWidget))

	class UProgressBar* PlayerHealth_ProgressBar;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* PlayerHP_TextNum;

	void UpdatePlayerHealth();

// 스태미나
	UPROPERTY(EditAnywhere, meta = (BindWidget))

	class UProgressBar* PlayerStamina_ProgressBar;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* PlayerStamina_TextNum;

	void UpdatePlayerStamina();

};
