// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ValheimPlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class VALHEIM_API UValheimPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ValheimPlayerAnimInstance)
	float Speed = 0.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ValheimPlayerAnimInstance)
	bool IsAir;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ValheimPlayerAnimInstance)
	float Direction = 0.f;
};
