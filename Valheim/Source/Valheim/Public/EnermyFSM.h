// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "Component/ActorComponent.h"
#include "EnermyFSM.generated.h"


UENUM(BlueprintType)
enum class EEnermyState : uint8
{
	Idle,
	Move,
	Attack,
	Damage,
	Die,

};





UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VALHEIM_API UEnermyFSM : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnermyFSM();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	

UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category ="FSM")
EEnermyState mState = EEnermyState::Idle;

void IdleState();

UPROPERTY(EditDefaultsOnly, Category=FSM)
float idleDelayTime = 2;

float currentTime = 0;

UPROPERTY(VisibleAnywhere, Category=FSM)
class AValheimPlayer* target;
UPROPERTY()
class AEnermyTroll* me;
UPROPERTY(EditAnywhere, Category=FSM)
float attackRange = 100.0f;

UPROPERTY(EditAnywhere, Category=FSM)
float attackDelayTime = 2.0f;
// 피격 알림 이벤트 함수
void OnDamageProcess(int32 damage);

UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category =FSM)
int32 hp = 7;

UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category =FSM)
float damageDelayTime = 2.0f;
// 죽은뒤 아래로 사라지는 속도
UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category =FSM)
float dieSpeed = 50.0f;
// 사용중인 애니메이션 블루프린트
UPROPERTY()
class UEnermyAnim* anim;

void OnAttackEnd();

UPROPERTY()
class AAIController* ai;

FVector randomPos;

bool GetRandomPositionInNavMesh(FVector certerLocation, float radius, FVector
	& dest);


UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = FSM)
bool bDieDone = false;

void MoveState();
void AttackState();
void DamegeState();
void DieState();



};
