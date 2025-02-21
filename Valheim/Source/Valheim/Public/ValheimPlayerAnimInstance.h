// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Components/TimeLineComponent.h"
#include "ValheimPlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class VALHEIM_API UValheimPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UValheimPlayerAnimInstance();

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ValheimPlayerAnimInstance)
	float Speed = 0.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ValheimPlayerAnimInstance)
	bool IsAir;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ValheimPlayerAnimInstance)
	float Direction = 0.f;
	
	
	// KMS 2.20 애니메이션 몽타주 마지막에 공격다시 이동속도 리셋
	UFUNCTION()
	void AnimNotify_AttackEnd();

	UPROPERTY()
	class AValheimPlayer* player;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerAnimation)
	class UAnimMontage* RollAnimMontage;

	// void PlayRollAnim(float DeltaSeconds);
	void PlayRollAnim();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "TimeLine", Meta = (AllowPrivateAccess = "true"))
	UCurveFloat* RollCurve;
	
	FTimeline LerpTimeline;

	float RollDuration = 0.f;
	float currentTime = 0.f;
	bool bAnimRolling;
	
	FTimeline RollTimeline;

	FVector RollStartLocation;
	FVector RollDirection;
	FVector RollTargetLocation;

	void TickRoll(float Value);
	void OnRollFinished();


};
