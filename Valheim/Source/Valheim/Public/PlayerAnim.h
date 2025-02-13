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
	// 플레이어 이동 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerAnim)
	float speed = 0;
	// 플레이어 좌우 이동 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerAnim)
	float direction = 0;

	// 매 프레임 갱신되는 함수
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

};
