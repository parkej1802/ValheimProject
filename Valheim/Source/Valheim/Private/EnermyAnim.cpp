// Fill out your copyright notice in the Description page of Project Settings.


#include "EnermyAnim.h"
#include "EnermyTroll.h"

UEnermyAnim::UEnermyAnim()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DeathMontageObj(TEXT("/Script/Engine.AnimMontage'/Game/Fab/troll/source/TrollDeath.TrollDeath'"));
	if (DeathMontageObj.Succeeded())
	{
		DeathAnimMontage = DeathMontageObj.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> DamagedMontageObj(TEXT("/Script/Engine.AnimMontage'/Game/Fab/troll/source/TrollDamaged.TrollDamaged'"));
	if (DamagedMontageObj.Succeeded())
	{
		DamagedAnimMontage = DamagedMontageObj.Object;
	}

	DeathDuration = DeathAnimMontage->GetPlayLength();
	DamagedDuration = DamagedAnimMontage->GetPlayLength();
}

void UEnermyAnim::OnEndAttackAnimation()
{
	bAttackPlay = false;
}

void UEnermyAnim::AnimNotify_DieEnd()
{
	if (AEnermyTroll* enermy = Cast<AEnermyTroll>(TryGetPawnOwner()))
	{
		//enermy->fsm->onDieEnd();
	}
}
