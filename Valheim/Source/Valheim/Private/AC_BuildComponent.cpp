// Fill out your copyright notice in the Description page of Project Settings.


#include "AC_BuildComponent.h"
#include "ValheimPlayer.h"
#include "CollisionQueryParams.h"
#include "AC_CraftingComponent.h"
#include "AC_InventoryComponent.h"


// Sets default values for this component's properties
UAC_BuildComponent::UAC_BuildComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
}


// Called when the game starts
void UAC_BuildComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();

	if (Owner)
	{
		PlayerCharacter = Cast<AValheimPlayer>(Owner);
		if (PlayerCharacter) {
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("PlayerCharacter!"));
		}
		
		FString DataTablePath = TEXT("/Game/UP/BuildingMaterial/Buildable/S_BuildableDB.S_BuildableDB");
		BuildableDB = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *DataTablePath));

		GetDataTableRowNames();
	}


}


// Called every frame
void UAC_BuildComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UAC_BuildComponent::SetCameraBS(UCameraComponent* NewCamera)
{
	CameraBS = NewCamera;
}

void UAC_BuildComponent::SetBuildTransform(FTransform* BT)
{
	BuildTransform = *BT;
}

void UAC_BuildComponent::BuildDelay(FName BuildingName)
{
	if (IsBuildMode)
	{
		FTimerHandle TH_DelayManager;
		GetWorld()->GetTimerManager().SetTimer(TH_DelayManager, FTimerDelegate::CreateLambda([this, BuildingName]() {
			this->BuildCycle(BuildingName);
			}), 0.01f, false);
	}
	else {
		//StopBuildMode();
	}
}

void UAC_BuildComponent::SpawnBuildGhost(FName BuildingName)
{
	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("SpawnBuildGhost"));
	if (PlayerCharacter)
	{
		UStaticMeshComponent* NewBuildGhost = Cast<UStaticMeshComponent>(
			PlayerCharacter->AddComponentByClass(UStaticMeshComponent::StaticClass(), false, BuildTransform, false));
				
		if (NewBuildGhost)
		{
			BuildGhost = NewBuildGhost;

			FBuildingStruct& BuildingData = BuildableDataMap[BuildingName];

			UStaticMesh* MeshAsset = BuildingData.Mesh;

			if (MeshAsset)
			{
				BuildGhost->SetStaticMesh(MeshAsset);
				BuildGhost->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("BuildGhost!"));
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Failed BuildGhost"));
			}

		}
	}
}

void UAC_BuildComponent::BuildCycle(FName BuildingName)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Buil Cycle!"));

	FVector CameraLocation = CameraBS->GetComponentLocation();
	FVector CameraForwardVector = CameraBS->GetForwardVector();
	
	FVector calculateFV = CameraForwardVector * 350 + CameraLocation;
	FVector calcalateFV2 = CameraForwardVector * 1000 + CameraLocation;

	FHitResult HitResult;

	FCollisionQueryParams CollisionParams;

	AActor* OwnerActor = GetOwner();
	if (OwnerActor)
	{
		CollisionParams.AddIgnoredActor(OwnerActor);
	}

	FBuildingStruct& BuildingData = BuildableDataMap[BuildingName];

	TEnumAsByte<ETraceTypeQuery> TraceInfo = BuildingData.TraceType;

	ECollisionChannel CollisionChannel = UEngineTypes::ConvertToCollisionChannel(BuildingData.TraceType);

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, calculateFV, calcalateFV2, CollisionChannel, CollisionParams);

	FRotator Rotation = BuildTransform.GetRotation().Rotator();
	FVector Scale = BuildTransform.GetScale3D();

	if (bHit)
	{
		FVector ImpactLocation = HitResult.ImpactPoint;
		FTransform SetTransform = FTransform(Rotation, ImpactLocation, Scale);
		HitActor = HitResult.GetActor();
		HitComponent = HitResult.GetComponent();

		/*
		if (HitComponent)
		{
			FString ComponentName = HitComponent->GetName();
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("HitComponent Name: %s"), *ComponentName));
			}
		}
		*/

		SetBuildTransform(&SetTransform);

		if (BuildGhost != nullptr) {
			FBuildDetectResult DetectResult = DetectBuildBox();
			if (DetectResult.Found) {
				FTransform bTransform = DetectResult.BuildTransform;
				BuildTransform = bTransform;
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Snapping Success!!"));
			}
			
			GiveBuildColor(true);
			//BuildDelay();
		}
	}
	else {
		FVector TraceEnd = HitResult.TraceEnd;
		FTransform SetTransform = FTransform(Rotation, TraceEnd, Scale);
		SetBuildTransform(&SetTransform);

		if (BuildGhost != nullptr) {
			GiveBuildColor(false);
		}
	}

	BuildDelay(BuildingName);
}

void UAC_BuildComponent::GiveBuildColor(bool isGreen)
{
	CanBuild = isGreen;
	
	int32 NumMaterial = BuildGhost->GetNumMaterials();

	for (int32 i = 0; i < NumMaterial; i++) {
		if (isGreen) {
			UMaterial* GreenMaterial = LoadObject<UMaterial>(nullptr, TEXT("/Script/Engine.Material'/Game/UP/Material/M_GreenColor.M_GreenColor'"));
			if (GreenMaterial)
			{
				BuildGhost->SetMaterial(i, GreenMaterial);
			}
		}
		else {
			UMaterial* RedMaterial = LoadObject<UMaterial>(nullptr, TEXT("/Script/Engine.Material'/Game/UP/Material/M_RedColor.M_RedColor'"));
			if (RedMaterial)
			{
				BuildGhost->SetMaterial(i, RedMaterial);
			}
		}
	}
	BuildGhost->SetWorldTransform(BuildTransform);
}

void UAC_BuildComponent::LaunchBuildMode(FName BuildingName)
{
	if (IsBuildMode)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("IsBuildMode True"));
		StopBuildMode();
	}
	else {
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("IsBuildMode false"));
		IsBuildMode = true;
		SpawnBuildGhost(BuildingName);
		BuildCycle(BuildingName);
	}
}

void UAC_BuildComponent::StopBuildMode()
{
	CanBuild = false;
	IsBuildMode = false;

	if (BuildGhost != nullptr) {
		PlayerCharacter->DestroyComponent(BuildGhost);
		BuildGhost = nullptr;
	}
}

void UAC_BuildComponent::GetDataTableRowNames()
{
	if (BuildableDB)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("BuildableDB is valid!"));
		TArray<FName> RowNames = BuildableDB->GetRowNames();

		for (FName& RowName : RowNames)
		{
			FBuildingStruct* RowData = BuildableDB->FindRow<FBuildingStruct>(RowName, TEXT("Context"));
			if (RowData)
			{
				BuildableDataArray.Add(*RowData);
				BuildableDataMap.Add(RowName, *RowData);
			}
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Failed DB"));
	}
}

void UAC_BuildComponent::ChangeMesh()
{
	if (IsValid(BuildGhost)) {
		FBuildingStruct& BuildingData = BuildableDataArray[BuildID];

		UStaticMesh* MeshAsset = BuildingData.Mesh;
		BuildGhost->SetStaticMesh(MeshAsset);
	}
}

void UAC_BuildComponent::SpawnBuild(FName BuildingName)
{
	//FBuildingStruct& BuildingData = BuildableDataArray[BuildID];
	FBuildingStruct& BuildingData = BuildableDataMap[BuildingName];

	TSubclassOf<AActor> BuildingActor = BuildingData.Actor;

	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(BuildingActor, BuildTransform);

	//IBuildInterface::Execute_SetMesh(SpawnedActor, BuildingData.Mesh);
}

void UAC_BuildComponent::DestroyBuild()
{
	if (HitActor && HitActor->Implements<UBuildInterface>()) {
		IBuildInterface* BuildActor = Cast<IBuildInterface>(HitActor);

		if (BuildActor)
		{
			FString ActorName = HitActor->GetName();
			UE_LOG(LogTemp, Warning, TEXT("Destroyed Actor: %s"), *ActorName);
			HitActor->Destroy();
			HitActor = nullptr;
		}
	}
}

void UAC_BuildComponent::RotateRight()
{
	FQuat NewRotation = FQuat(FRotator(0.0f, 90.0f * GetWorld()->GetDeltaSeconds(), 0.0f));

	BuildTransform.SetRotation(BuildTransform.GetRotation() * NewRotation);

	BuildGhost->SetWorldTransform(BuildTransform);

	//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Rotating RIght!"));

}

void UAC_BuildComponent::RotateLeft()
{
	FQuat NewRotation = FQuat(FRotator(0.0f, -90.0f * GetWorld()->GetDeltaSeconds(), 0.0f));

	BuildTransform.SetRotation(BuildTransform.GetRotation() * NewRotation);
	BuildGhost->SetWorldTransform(BuildTransform);
	//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Rotating RIght!"));
}

bool UAC_BuildComponent::IsIngredientsEnough(FName BuildingName)
{
	FCraftableStruct* CraftItem = CraftComp->CraftableDataMap.Find(BuildingName);

	for (TPair<TSubclassOf<AItem>, int32>& Ingredient : CraftItem->Ingredients)
	{
		TSubclassOf<AItem> RequiredItem = Ingredient.Key;
		int32 RequiredAmount = Ingredient.Value;

		bool bHasEnough = false;

		for (FInventoryStruct& InventoryItem : InventoryComp->ItemsInInventory)
		{
			if (InventoryItem.ItemClass == RequiredItem && InventoryItem.Quantity >= RequiredAmount)
			{
				bHasEnough = true;

				break;
			}
		}

		if (!bHasEnough)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Not enough materials for %s"), *RequiredItem->GetName()));
				
			return false;
		}
	}

	for (TPair<TSubclassOf<AItem>, int32>& Ingredient : CraftItem->Ingredients) {
		TSubclassOf<AItem> RequiredItem = Ingredient.Key;
		int32 RequiredAmount = Ingredient.Value;

		for (FInventoryStruct& InventoryItem : InventoryComp->ItemsInInventory)
		{
			if (InventoryItem.ItemClass == RequiredItem && InventoryItem.Quantity >= RequiredAmount)
			{
				InventoryItem.Quantity -= RequiredAmount;
				if (InventoryItem.Quantity == 0) {
					InventoryItem = FInventoryStruct();
				}
			}
		}
	}

	return true;
}

FBuildDetectResult UAC_BuildComponent::DetectBuildBox()
{
	FBuildDetectResult Result;
	Result.Found = false;

	if (HitActor && HitActor->Implements<UBuildInterface>())
	{
		IBuildInterface* BuildActor = Cast<IBuildInterface>(HitActor);

		if (BuildActor)
		{

			//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("BuildActor Valid!!!"));

			TArray<UBoxComponent*> TraceCollision = IBuildInterface::Execute_GetBoxCollision(HitActor);

			for (UBoxComponent* Box : TraceCollision)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("UBoxComponent Valid!!!"));
				/*if (Box)
				{
					FString BoxName = Box->GetName();
					GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, *BoxName);
				}*/

				if (Box == HitComponent)
				{
					Result.Found = true;
					Result.BuildTransform = HitComponent->GetComponentTransform();
					//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("BoxCollisionFound"));
					break;
				}
			}
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No BuildActor"));
		}
	}

	return Result;
}

