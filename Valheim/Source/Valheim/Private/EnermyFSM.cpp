// Fill out your copyright notice in the Description page of Project Settings.


#include "EnermyFSM.h"
#include "ValheimPlayer.h"
#include "EnermyTroll.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UEnermyFSM::UEnermyFSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEnermyFSM::BeginPlay()
{
	Super::BeginPlay();

	// ...
	auto actor = UGameplayStatics::GetActorOfClass(GetWorld(), AValheimPlayer::StaticClass());
	target = Cast<AValheimPlayer>(actor);
	me = Cast<AEnermyTroll>(GetOwner());
	
}


// Called every frame
void UEnermyFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
/*
	if (mState == EEnermyState::Idle)
	{
	}
	switch (mState)
	{
	case EEnermyState::Idle:
		break;
	}
*/
	// ...
	FString logMsg = UEnum::GetValueAsString(mState);
	GEngine->AddOnScreenDebugMessage(0, 1, FColor::Cyan, logMsg);

	switch(mState)
	{
		case EEnermyState::Idle:IdleState();
			break;
		case EEnermyState::Move:MoveState();
			break;
		case EEnermyState::Attack:AttackState();
			break;
		case EEnermyState::Damage:DamegeState();
			break;
		case EEnermyState::Die:DieState();
			break;
	}
}

void UEnermyFSM::IdleState()
{
	currentTime += GetWorld()->DeltaTimeSeconds;
	
	if (currentTime > idleDelayTime)
	{
		mState = EEnermyState::Move;
		currentTime = 0;
	}
}

void UEnermyFSM::OnDamageProcess()
{
	me->Destroy();
}

void UEnermyFSM::MoveState()
{
	if (!target || !me) return;
	FVector destination = target->GetActorLocation();
	FVector dir = destination - me->GetActorLocation();
	me->AddMovementInput(dir.GetSafeNormal());

	if (dir.Size() < attackRange)
	{
		mState = EEnermyState::Attack;
	}
}

void UEnermyFSM::AttackState()
{
	
	currentTime += GetWorld()->DeltaTimeSeconds;
	if (currentTime > attackDelayTime)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Red, TEXT("Attack!!"));

		currentTime = 0;

	}

	float distance = FVector::Distance(target->GetActorLocation(), me->GetActorLocation());
	if (distance > attackRange)
	{
		mState = EEnermyState::Move;
	}


}

void UEnermyFSM::DamegeState()
{

}

void UEnermyFSM::DieState()
{

}

