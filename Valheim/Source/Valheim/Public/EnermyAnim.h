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
	UEnermyAnim();
UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category=FSM)
	EEnermyState animState;

UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category=FSM)
bool bAttackPlay = false;


UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category=FSM)
bool bDamaged = false;

UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category=FSM)
bool bDead = false;

UFUNCTION(BlueprintCallable, Category = FSMEvent)
void OnEndAttackAnimation();

UFUNCTION(BlueprintImplementableEvent, Category = FSMEvent)
void PlayDamageAnim(FName SectionName);


UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
class UAnimMontage* DeathAnimMontage;

void PlayDeathAnim();
void EndDeathAnim();

UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
class UAnimMontage* DamagedAnimMontage;

void PlayDamagedAnim();
void EndDamagedAnim();

float DamagedDuration = 0.f;
float DeathDuration = 0.f;
float currentTime = 0.f;


FORCEINLINE
void onDieEnd()
{
	bool bDieDone = true;
}

UFUNCTION()
void AnimNotify_DieEnd();


};
