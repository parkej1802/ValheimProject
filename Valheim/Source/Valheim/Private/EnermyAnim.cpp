// Fill out your copyright notice in the Description page of Project Settings.


#include "EnermyAnim.h"
#include "EnermyTroll.h"

void UEnermyAnim::OnEndAttackAnimation()
{
	if (AEnermyTroll* enermy = Cast<AEnermyTroll>(TryGetPawnOwner()))
	{
		enermy->fsm->OnAttackEnd();
	}
}

void UEnermyAnim::AnimNotify_DieEnd()
{
	if (AEnermyTroll* enermy = Cast<AEnermyTroll>(TryGetPawnOwner()))
	{
		//enermy->fsm->onDieEnd();
	}
}
