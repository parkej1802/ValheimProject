#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "Camera/CameraComponent.h"
#include "Engine/DataTable.h"
#include "S_Buildables.h"
#include "BuildInterface.h"

class AValheimPlayer;
class UAC_CraftingComponent;
class UAC_InventoryComponent;

#include "AC_BuildComponent.generated.h"

USTRUCT(BlueprintType)
struct FBuildDetectResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "SnapDetect")
	bool Found;

	UPROPERTY(BlueprintReadWrite, Category = "SnapDetect")
	FTransform BuildTransform;
};

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class VALHEIM_API UAC_BuildComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAC_BuildComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

// BuildingSystem
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BuildingSystem)
	class UCameraComponent* CameraBS;

	void SetCameraBS(UCameraComponent* NewCamera);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BuildingSystem)
	class UStaticMeshComponent* BuildGhost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BuildingSystem)
	bool IsBuildMode = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BuildingSystem)
	bool CanBuild = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BuildingSystem)
	int BuildID = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BuildingSystem)
	FTransform BuildTransform;

	void SetBuildTransform(FTransform* BT);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BuildingSystem)
	AValheimPlayer* PlayerCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	UDataTable* BuildableDB;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data)
    TArray<FBuildingStruct> BuildableDataArray;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data)
	TMap<FName, FBuildingStruct> BuildableDataMap;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data)
	AActor* HitActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data)

	UPrimitiveComponent* HitComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data)
	UAC_CraftingComponent* CraftComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data)
	UAC_InventoryComponent* InventoryComp;

// Build Functions
public:
	void BuildDelay(FName BuildingName);
	void SpawnBuildGhost(FName BuildingName);
	void BuildCycle(FName BuildingName);
	void GiveBuildColor(bool isGreen);
	void LaunchBuildMode(FName BuildingName);
	void StopBuildMode();
	void GetDataTableRowNames();
	void ChangeMesh();
	void SpawnBuild(FName BuildingName);
	void DestroyBuild();
	void RotateRight();
	void RotateLeft();
	bool IsIngredientsEnough(FName BuildingName);
	bool LocalFound = false;
	FBuildDetectResult DetectBuildBox();
};

