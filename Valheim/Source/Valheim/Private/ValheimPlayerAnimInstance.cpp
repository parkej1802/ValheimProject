// Fill out your copyright notice in the Description page of Project Settings.


#include "ValheimPlayerAnimInstance.h"
#include "../Public/ValheimPlayer.h"


void UValheimPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AValheimPlayer* player = Cast<AValheimPlayer>(TryGetPawnOwner());
	if (!player) return;

	FVector velocity = player->GetVelocity();
	FVector forwardVector = player->GetActorForwardVector();

	Speed = FVector::DotProduct(velocity, forwardVector);

	IsAir = player->GetCharacterMovement()->IsFalling();

	FVector rightVector = player->GetActorRightVector();
	Direction = FVector::DotProduct(velocity, rightVector);
	
}
