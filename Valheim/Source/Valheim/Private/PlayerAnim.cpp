// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnim.h"
#include "ValheimPlayer.h"

void UPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	// 1. 플레이어 불러오기
	auto ownerPawn = TryGetPawnOwner();
	// 2. 플레이어로 캐스팅하기
	auto player = Cast<AValheimPlayer>(ownerPawn);
	// 캐스팅에 성공하면
	if(player)
	{ 
		// 3. 이동 속도
		FVector Velocity = player->GetVelocity();
	    // 4. 플레이어의 전방 벡터가 필요
		FVector forwardVector = player->GetActorForwardVector();
		FVector rightVector = player->GetActorRightVector();
		// 5. speed에 값(내적) 할당하기
		speed = FVector::DotProduct(forwardVector, Velocity);
		direction = FVector::DotProduct(rightVector, Velocity);
		//UE_LOG(LogTemp, Log, TEXT("Hello, Unreal!%d"),speed);

	}
}

