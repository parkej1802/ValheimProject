// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
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

	// �¿� ȸ��
	void Turn(const FInputActionValue& inputValue);

	// ���� ȸ��
	void LookUp(const FInputActionValue& inputValue);

	// ������� �¿� �Է��� �޾Ƽ� �̵��ϰ� �ʹ�
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_Move;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* IA_Jump;

	void InputJump(const FInputActionValue& inputValue);

	// �̵��ӵ�
	UPROPERTY(EditAnywhere, Category = PlayerSetting)
	float WalkSpeed = 600.0f;

	// �̵� ����
	FVector Direction;

	void Move(const FInputActionValue& inputValue);
	
};
