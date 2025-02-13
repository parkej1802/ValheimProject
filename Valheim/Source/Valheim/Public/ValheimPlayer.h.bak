#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"

class UAC_BuildComponent;

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

	void LeftMouseButton(const FInputActionValue& inputValue);
};
