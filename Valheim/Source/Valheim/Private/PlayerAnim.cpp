// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnim.h"
#include "ValheimPlayer.h"

void UPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	// 1. �÷��̾� �ҷ�����
	auto ownerPawn = TryGetPawnOwner();
	// 2. �÷��̾�� ĳ�����ϱ�
	auto player = Cast<AValheimPlayer>(ownerPawn);
	// ĳ���ÿ� �����ϸ�
	if(player)
	{ 
		// 3. �̵� �ӵ�
		FVector Velocity = player->GetVelocity();
	    // 4. �÷��̾��� ���� ���Ͱ� �ʿ�
		FVector forwardVector = player->GetActorForwardVector();
		FVector rightVector = player->GetActorRightVector();
		// 5. speed�� ��(����) �Ҵ��ϱ�
		speed = FVector::DotProduct(forwardVector, Velocity);
		direction = FVector::DotProduct(rightVector, Velocity);
		//UE_LOG(LogTemp, Log, TEXT("Hello, Unreal!%d"),speed);

	}
}

