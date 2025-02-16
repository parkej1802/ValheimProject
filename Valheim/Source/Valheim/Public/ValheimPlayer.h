#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Blueprint/UserWidget.h"
#include "InventoryUI.h"
#include "CraftingUI.h"
#include "../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputAction.h"

class UAC_BuildComponent;
class UAC_InventoryComponent;
class UAC_CraftingComponent;

#include "ValheimPlayer.generated.h"

UCLASS()
class VALHEIM_API AValheimPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AValheimPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	APlayerController* pc;

public:
	UPROPERTY(EditDefaultsOnly, Category = Camera)
	class USpringArmComponent* springArmComp;

	UPROPERTY(EditDefaultsOnly, Category = Camera)
	class UCameraComponent* tpsCamComp;

public:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* IMC_TPS;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_LookUp;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_Turn;


	void Turn(const FInputActionValue& inputValue);

	void LookUp(const FInputActionValue& inputValue);

	// 사용자의 좌우 입력을 받아서 이동하고 싶다
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_Move;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_Jump;

	void InputJump(const FInputActionValue& inputValue);

	UPROPERTY(EditAnywhere, Category = PlayerSetting)
	float WalkSpeed = 600.0f;

	FVector Direction;

	void Move(const FInputActionValue& inputValue);

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_Sprint;
	
	// 구르기
	UPROPERTY(EditDefaultsOnly, Category = "Input")

	class UInputAction* IA_Roll;

// Building System
public:
	UPROPERTY(EditDefaultsOnly, Category = BuildingSystem)
	UAC_BuildComponent* BuildComp;

	UPROPERTY(EditDefaultsOnly, Category = BuildingSystem)
	class UInputAction* IA_BuildMode;

	void BuildModeOn();
	void DestroyComponent(UActorComponent* BC);

	UPROPERTY(EditDefaultsOnly, Category = BuildingSystem)
	class UInputAction* IA_WheelUp;

	UPROPERTY(EditDefaultsOnly, Category = BuildingSystem)
	class UInputAction* IA_WheelDown;

	void WheelUp(const FInputActionValue& inputValue);
	void WheelDown(const FInputActionValue& inputValue);

	UPROPERTY(EditDefaultsOnly, Category = BuildingSystem)
	class UInputAction* IA_LeftMouseButton;

	UPROPERTY(EditDefaultsOnly, Category = BuildingSystem)
	class UInputAction* IA_RightMouseButton;

	void LeftMouseButton(const FInputActionValue& inputValue);
	void RightMouseButton(const FInputActionValue& inputValue);

	UPROPERTY(EditDefaultsOnly, Category = BuildingSystem)
	class UInputAction* IA_RotateRightR;

	UPROPERTY(EditDefaultsOnly, Category = BuildingSystem)
	class UInputAction* IA_RotateLeftQ;

	void RotateRightR(const FInputActionValue& inputValue);
	void RotateLeftQ(const FInputActionValue& inputValue);


// Crafting System
public:
	UPROPERTY(EditAnywhere, Category = CraftingSystem)
	class UInputAction* IA_CraftMode;

	UPROPERTY(EditAnywhere, Category = CraftingSystem)
	TSubclassOf<UUserWidget> CraftWidget;

	void CraftModeOn();
	bool IsCraftModeOn = false;

	class UCraftingUI* CraftUI;

	UPROPERTY(EditAnywhere, Category = CraftingSystem)
	class UAC_CraftingComponent* CraftingComp;

// Inventory System
public:
	UPROPERTY(EditAnywhere, Category = InventorySystem)
	class UInputAction* IA_InventoryMode;

	UPROPERTY(EditAnywhere, Category = InventorySystem)
	class UInputAction* IA_PickUp;

	void PickUp();

	void InventoryModeOn();
	bool IsInventoryModeOn = false;

	UPROPERTY(EditAnywhere, Category = InventorySystem)
	TSubclassOf<UUserWidget> InventoryWidget;

	class UInventoryUI* InventoryUI;

	UPROPERTY(EditDefaultsOnly, Category = BuildingSystem)
	class UAC_InventoryComponent* InventoryComp;

protected:
	// 달리기
	void SprintStart(const FInputActionValue& inputValue);
	void SprintEnd(const FInputActionValue& inputValue);

	UPROPERTY(EditAnywhere, Category = PlayerSetting)
	float SprintSpeed = 900.0f;


	// 구르기
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerSetting)
	bool Rollcheck = false;
	void Roll(const FInputActionValue& inputValue);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerSetting)
	float RollSpeed = 1800.0f;

};
