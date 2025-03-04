// Fill out your copyright notice in the Description page of Project Settings.


#include "NS_MeleeAttack.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"
#include "Engine/Engine.h"
#include "Tree.h"
#include "EnermyTroll.h"
#include "Engine/DamageEvents.h"

void UNS_MeleeAttack::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	if (!MeshComp) return;

	AActor* Owner = MeshComp->GetOwner();
	if (!Owner) return;

	UWorld* World = MeshComp ? MeshComp->GetWorld() : nullptr;
	if (!World)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("World is nullptr!"));
		}
		return;
	}

	FVector StartLocation = MeshComp->GetSocketLocation(FName("Weapon"));
	FVector EndLocation = MeshComp->GetSocketLocation(FName("WeaponTip"));

	if (GEngine)
	{
		/*GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan,
			FString::Printf(TEXT("Weapon Position: %s"), *StartLocation.ToString()));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan,
			FString::Printf(TEXT("WeaponTip Position: %s"), *EndLocation.ToString()));*/
	}

	float SphereRadius = 30.0f;
	TArray<FHitResult> HitResults;
	FCollisionQueryParams TraceParams(FName(TEXT("MeleeAttackTrace")), false, Owner);

	bool bHit = World->SweepMultiByChannel(
		HitResults,
		StartLocation,
		EndLocation,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel10,
		FCollisionShape::MakeSphere(SphereRadius),
		TraceParams
	);


	if (World)
	{
		//DrawDebugSphere(World, StartLocation, SphereRadius, 12, FColor::Red, false, 0.5f);
		//DrawDebugSphere(World, EndLocation, 40, 12, FColor::Blue, false, 0.5f);
		//DrawDebugLine(World, StartLocation, EndLocation, FColor::Green, false, 0.5f);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("GetWorld is nullptr!"));
	}


	if (bHit)
	{
		for (const FHitResult& Hit : HitResults)
		{
			AActor* HitActor = Hit.GetActor();
			if (HitActor && HitActor != Owner)
			{
				if (HitActor->IsA<ATree>())
				{
					ATree* HitTree = Cast<ATree>(HitActor);
					if (HitTree)
					{
						HitTree->TakeDamage(15.0f);
					}
				}
				// 2.24 KMS 적에게 damage AI솔루션
				if (HitActor->IsA<AEnermyTroll>())
				{
					AEnermyTroll* Enemy = Cast<AEnermyTroll>(HitActor);
					if (Enemy)
					{
						FDamageEvent DamageEvent;
						Enemy->TakeDamage(20.0f, DamageEvent, nullptr, Owner);
					}
				}

				/*if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("Hit: %s"), *HitActor->GetName())
					);
				}*/
			}
		}
	}
}

