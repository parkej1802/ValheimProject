// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnim.generated.h"

/**
 * 
 */
UCLASS()
class VALHEIM_API UPlayerAnim : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	// �÷��̾� �̵� �ӵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerAnim)
	float speed = 0;
	// �÷��̾� �¿� �̵� �ӵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerAnim)
	float direction = 0;

	// �� ������ ���ŵǴ� �Լ�
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

};
