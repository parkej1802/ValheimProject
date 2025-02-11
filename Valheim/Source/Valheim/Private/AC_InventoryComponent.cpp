// Fill out your copyright notice in the Description page of Project Settings.


#include "AC_InventoryComponent.h"
#include "ValheimPlayer.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values for this component's properties
UAC_InventoryComponent::UAC_InventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UAC_InventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAC_InventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAC_InventoryComponent::DetectPlayer()
{
	FVector CameraLocation = ConnectedActor->tpsCamComp->GetComponentLocation();
	FVector CameraForwardVector = ConnectedActor->tpsCamComp->GetForwardVector();

	float TargetArmLength = ConnectedActor->springArmComp->TargetArmLength + 500;

	FVector calculateFV = CameraLocation;
	FVector calculateFV2 = CameraForwardVector * TargetArmLength + calculateFV;

	FHitResult HitResult;

	FCollisionQueryParams CollisionParams;

	AActor* OwnerActor = GetOwner();
	if (OwnerActor)
	{
		CollisionParams.AddIgnoredActor(OwnerActor);
	}

	bool bHit = GetWorld()->SweepSingleByChannel(HitResult, calculateFV, calculateFV2, FQuat::Identity, ECC_Visibility, FCollisionShape::MakeSphere(10.0f), CollisionParams);

	if (bHit)
	{
		FString HitMessage = FString::Printf(TEXT("Hit Actor: %s at Impact Point: %s"), *HitResult.GetActor()->GetName(), *HitResult.ImpactPoint.ToString());
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, HitMessage);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 50.0f, 12, FColor::Red, false, 1.0f);
		TryAddItem(HitResult.GetActor());
	}
	else
	{
		FString NoHitMessage = TEXT("No hit detected");
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, NoHitMessage);
	}
}

void UAC_InventoryComponent::TryAddItem(AActor* Actor)
{
	AMasterItem* MI = Cast<AMasterItem>(Actor);
	ItemData = MI->GetItemData();
}

void UAC_InventoryComponent::IsItemAlreadyInInventory()
{

}

