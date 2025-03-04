// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnermyFSM.h"
#include "EnermyAnim.generated.h"

/**
 * 
 */
UCLASS()
class VALHEIM_API UEnermyAnim : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category=FSM)
	EEnermyState animState = EEnermyState::Idle;
 UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category =FSM)
 bool bAttackPlay;

/* 2.23 å�� ������ ���� (���� ����)
public:
UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category=FSM)
	EEnermyState animState;

UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category=FSM)
bool bAttackPlay = false;
*/

UFUNCTION(BlueprintCallable, Category = FSMEvent)
void OnEndAttackAnimation();

UFUNCTION(BlueprintImplementableEvent, Category = FSMEvent)
void PlayDamageAnim(FName SectionName);

bool bDieDone;
//���� ���� �ִϸ��̼� ���Ῡ��

FORCEINLINE
void onDieEnd()
{
	 bDieDone = true;
}

UFUNCTION()
void AnimNotify_DieEnd();

UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category =FSM)
class UAnimMontage* EnermyMontage;


};
