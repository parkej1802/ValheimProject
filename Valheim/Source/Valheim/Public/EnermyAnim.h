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

/* 2.23 책에 나오는 내용 (변수 저장)
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
//죽음 상태 애니메이션 종료여부

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
