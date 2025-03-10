// Fill out your copyright notice in the Description page of Project Settings.


#include "EnermyTroll.h"
#include "EnermyFSM.h"
#include "Engine/SkeletalMesh.h"

// Sets default values
AEnermyTroll::AEnermyTroll()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Fab/troll/source/troll.troll'"));

	if (tempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(tempMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -88), FRotator(0, -90, 0));
	}
	GetMesh()->SetCollisionProfileName(FName("EnermyTroll"));

	fsm = CreateDefaultSubobject<UEnermyFSM>(TEXT("FSM"));

	// 애니메이션 블루프린트
	ConstructorHelpers::FClassFinder<UAnimInstance>tempClass(TEXT("/Script/Engine.AnimBlueprint'/Game/UP/Blueprints/ABP_TrollEnermy.ABP_TrollEnermy_C'"));
	if(tempClass.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(tempClass.Class);
	}
}

// Called when the game starts or when spawned
void AEnermyTroll::BeginPlay()
{
	Super::BeginPlay();




}

// Called every frame
void AEnermyTroll::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnermyTroll::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

