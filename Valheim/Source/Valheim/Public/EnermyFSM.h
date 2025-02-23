// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
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
float attackRange = 150.0f;

UPROPERTY(EditAnywhere, Category=FSM)
float attackDelayTime = 2.0f;

void OnDamageProcess();

void MoveState();
void AttackState();
void DamegeState();
void DieState();
		
};
