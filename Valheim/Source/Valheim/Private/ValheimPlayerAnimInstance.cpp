// Fill out your copyright notice in the Description page of Project Settings.


#include "ValheimPlayerAnimInstance.h"
#include "../Public/ValheimPlayer.h"

UValheimPlayerAnimInstance::UValheimPlayerAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> RollMontageObj(TEXT("/Game/UP/Animation/Roll_Montage.Roll_Montage"));
	if (RollMontageObj.Succeeded())
	{
		RollAnimMontage = RollMontageObj.Object;
	}

	RollDuration = RollAnimMontage->GetPlayLength();

}



void UValheimPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	player = Cast<AValheimPlayer>(TryGetPawnOwner());
	if (!player) return;

	FVector velocity = player->GetVelocity();
	FVector forwardVector = player->GetActorForwardVector();

	Speed = FVector::DotProduct(velocity, forwardVector);

	IsAir = player->GetCharacterMovement()->IsFalling();

	FVector rightVector = player->GetActorRightVector();
	Direction = FVector::DotProduct(velocity, rightVector);

	if (RollTimeline.IsPlaying())
	{
		RollTimeline.TickTimeline(DeltaSeconds);
	}
	
}

void UValheimPlayerAnimInstance::AnimNotify_AttackEnd()
{
	player->GetCharacterMovement()->MaxWalkSpeed = player->WalkSpeed;
}

//void UValheimPlayerAnimInstance::PlayRollAnim()
//{
//	if (player->IsRolling) { 
//		//FVector LastMoveVector = player->GetCharacterMovement()->GetLastInputVector();
//		//player->SetActorRotation(FRotator(LastMoveVector.X));
//		Montage_Play(RollAnimMontage);
//	}
//}

void UValheimPlayerAnimInstance::PlayRollAnim()
{
	if (!RollAnimMontage) return;

	player->GetMesh()->GetAnimInstance()->SetRootMotionMode(ERootMotionMode::RootMotionFromEverything);
	Montage_Play(RollAnimMontage);
	player->IsRolling = true;

	RollStartLocation = player->GetActorLocation();
	RollDirection = player->GetActorForwardVector();
	RollTargetLocation = RollStartLocation + (RollDirection * 1000.0f);

	player->SetActorRotation(FRotator(0.f, player->GetActorRotation().Yaw, 0.f));

	FOnTimelineFloat ProgressFunction;
	ProgressFunction.BindUFunction(this, FName("TickRoll"));
	RollTimeline.AddInterpFloat(RollCurve, ProgressFunction);

	FOnTimelineEvent FinishFunction;
	FinishFunction.BindUFunction(this, FName("OnRollFinished"));
	RollTimeline.SetTimelineFinishedFunc(FinishFunction);

	RollTimeline.SetPlayRate(1.0f / RollAnimMontage->GetPlayLength());
	RollTimeline.PlayFromStart();
}

void UValheimPlayerAnimInstance::TickRoll(float Value)
{
	FVector NewLocation = FMath::Lerp(RollStartLocation, RollTargetLocation, Value);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("TickRoll"));
	player->SetActorLocation(NewLocation);
}

void UValheimPlayerAnimInstance::OnRollFinished()
{
	player->IsRolling = false;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("OnRollFinished"));
	player->SetActorLocation(RollTargetLocation);
	player->SetActorRotation(FRotator(0.f, player->GetActorRotation().Yaw, 0.f));
}
