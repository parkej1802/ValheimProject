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
UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category=FSM)
	EEnermyState animState;

UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category=FSM)
bool bAttackPlay = false;


UFUNCTION(BlueprintCallable, Category = FSMEvent)
void OnEndAttackAnimation();

UFUNCTION(BlueprintImplementableEvent, Category = FSMEvent)
void PlayDamageAnim(FName SectionName);

//���� ���� �ִϸ��̼� ���Ῡ��


FORCEINLINE
void onDieEnd()
{
	bool bDieDone = true;
}

UFUNCTION()
void AnimNotify_DieEnd();


};
