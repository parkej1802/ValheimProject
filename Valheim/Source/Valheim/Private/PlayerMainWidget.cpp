// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMainWidget.h"
#include "ValheimPlayer.h"

void UPlayerMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	APlayerController* PlayerController = GetOwningPlayer();
	if (PlayerController)
	{
		APawn* PlayerPawn = PlayerController->GetPawn();

		PlayerCharacter = Cast<AValheimPlayer>(PlayerPawn);
	}
	
}

void UPlayerMainWidget::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);
	UpdatePlayerHealth();
	UpdatePlayerStamina();
}

void UPlayerMainWidget::UpdatePlayerHealth()
{
	if (PlayerCharacter) {
		PlayerHealth_ProgressBar->SetPercent((float)PlayerCharacter->CurrentHealth / (float)PlayerCharacter->MaxHealth);
		PlayerHP_TextNum->SetText(FText::AsNumber(PlayerCharacter->CurrentHealth));
	}
}

void UPlayerMainWidget::UpdatePlayerStamina()
{
	if (PlayerCharacter->Stamina == 50) {
		PlayerStamina_ProgressBar->SetVisibility(ESlateVisibility::Hidden);
		PlayerStamina_TextNum->SetVisibility(ESlateVisibility::Hidden);
	}
	else {
		PlayerStamina_ProgressBar->SetVisibility(ESlateVisibility::Visible);
		PlayerStamina_TextNum->SetVisibility(ESlateVisibility::Visible);
	}

	if (PlayerCharacter) {
		PlayerStamina_ProgressBar->SetPercent((float)PlayerCharacter->Stamina / (float)PlayerCharacter->MaxStamina);
		PlayerStamina_TextNum->SetText(FText::AsNumber(PlayerCharacter->Stamina));
	}
}
