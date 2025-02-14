// Fill out your copyright notice in the Description page of Project Settings.


#include "AC_InventoryComponent.h"
#include "ValheimPlayer.h"
#include "InventoryUI.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values for this component's properties
UAC_InventoryComponent::UAC_InventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	ItemsInInventory.SetNum(15);
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
		//TryAddItem(HitResult.GetActor());
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
	//ItemData = MI->GetItemData();
}

void UAC_InventoryComponent::IsItemAlreadyInInventory()
{
	
}

void UAC_InventoryComponent::PickUpItem()
{
	FHitResult HitResult;

	FCollisionQueryParams CollisionParams;

	AActor* OwnerActor = GetOwner();
	if (OwnerActor)
	{
		CollisionParams.AddIgnoredActor(OwnerActor);
	}

	FVector PlayerLocation = OwnerActor->GetActorLocation();

	FVector StartLocationTrace = PlayerLocation - FVector(0.0f, 0.0f, 65.0f);

	bool bHit = GetWorld()->SweepSingleByChannel(HitResult, StartLocationTrace, StartLocationTrace, FQuat::Identity, ECC_Visibility, FCollisionShape::MakeSphere(120.0f), CollisionParams);

	if (bHit) {
		//DrawDebugSphere(GetWorld(), StartLocationTrace, 120, 12, FColor::Red, false, 2.0f);
		//DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 50.0f, 12, FColor::Red, false, 1.0f);
		//FString HitMessage = FString::Printf(TEXT("Hit Actor: %s at Impact Point: %s"), *HitResult.GetActor()->GetName(), *HitResult.ImpactPoint.ToString());
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, HitMessage);

		AItem* NearItem = Cast<AItem>(HitResult.GetActor());

		if (IsValid(NearItem)) {
			bool bItemAdded = false;

			for (int32 i = 0; i < ItemsInInventory.Num(); i++) {
				if (ItemsInInventory[i].Name.EqualTo(NearItem->Item.Name) && NearItem->Item.Stackable) {
					int32 TotalQuantity = ItemsInInventory[i].Quantity + NearItem->Item.Quantity;
					if (TotalQuantity <= 64) {
						ItemsInInventory[i].Quantity = TotalQuantity;
						ItemsInInventory[i].Name = NearItem->Item.Name;
						ItemsInInventory[i].Stackable = NearItem->Item.Stackable;
						ItemsInInventory[i].Thumbnail = NearItem->Item.Thumbnail;
						ItemsInInventory[i].Mesh = NearItem->Item.Mesh;
						bItemAdded = true;
						NearItem->Destroy();
						break;
					}
				}
			}
			if (!bItemAdded)
			{
				for (int32 i = 0; i < ItemsInInventory.Num(); i++)
				{
					if (ItemsInInventory[i].Quantity == 0)
					{
						ItemsInInventory[i] = NearItem->Item;
						NearItem->Destroy();
						bItemAdded = true;
						break;
					}
				}
			}
		}
	}
}

