// Fill out your copyright notice in the Description page of Project Settings.


#include "EnermyFSM.h"
#include "ValheimPlayer.h"
#include "EnermyTroll.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "EnermyAnim.h"
//#include "AIController.h"
#include "NavigationSystem.h"



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

	anim = Cast<UEnermyAnim>(me->GetMesh()->GetAnimInstance());

	////AAIController 할당하기
	//ai = Cast<AAIController>(me->GetController());
	//
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

		anim->animState = mState;
	}
}

void UEnermyFSM::OnDamageProcess()
{
	hp--;
	if (hp > 0)
	{
		mState = EEnermyState::Damage;

		currentTime = 0;
		// 피격 애니메이션 재생
		int32 index = FMath::RandRange(0, 1);
		FString SectionName = FString::Printf(TEXT("Damage%d"), index);
		anim->PlayDamageAnim(FName(*SectionName));
	}

	else
	{
		mState = EEnermyState::Die;
		me->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		// 죽음 애니메이션 재생
		anim->PlayDamageAnim(TEXT("Die"));
	}
	anim->animState = mState;

	

	
}

bool UEnermyFSM::GetRandomPositionInNavMesh(FVector certerLocation, float radius, FVector& dest)
{
	auto ns = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	FNavLocation loc;
	bool result = ns->GetRandomReachablePointInRadius(certerLocation, radius, loc);
	dest = loc.Location;
	return result;
}

void UEnermyFSM::MoveState()
{
	//if (!target || !me) return;
	FVector destination = target->GetActorLocation();
	FVector dir = destination - me->GetActorLocation();
	//me->AddMovementInput(dir.GetSafeNormal());
	//ai->MoveToLocation(destination);

	if (dir.Size() < attackRange)
	{
		mState = EEnermyState::Attack;

		anim->animState = mState;

		anim->bAttackPlay = true;

		currentTime = attackDelayTime;


	}
}

void UEnermyFSM::AttackState()
{
	
	currentTime += GetWorld()->DeltaTimeSeconds;
	if (currentTime > attackDelayTime)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Red, TEXT("Attack!!"));

		currentTime = 0;
		anim->bAttackPlay = true;

	}

	float distance = FVector::Distance(target->GetActorLocation(), me->GetActorLocation());
	if (distance > attackRange)
	{
		mState = EEnermyState::Move;
		anim->animState = mState;
	}


}

void UEnermyFSM::DamegeState()
{
	currentTime += GetWorld()->DeltaTimeSeconds;

	if (currentTime > damageDelayTime)
	{
		mState = EEnermyState::Idle;
		currentTime = 0;

		anim->animState = mState;

	}
}

void UEnermyFSM::DieState()
{
	if (!bDieDone) return;
	
	

	FVector p0 = me->GetActorLocation();
	FVector vt = FVector::DownVector * dieSpeed * GetWorld()->DeltaTimeSeconds;
	FVector p = p0 + vt;
	me->SetActorLocation(p);


	if (p.Z < -200.0f)
	{
		me->Destroy();
	}
}

