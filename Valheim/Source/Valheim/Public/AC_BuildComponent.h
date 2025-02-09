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
	AActor* HitActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data)

	UPrimitiveComponent* HitComponent;


// Build Functions
public:
	void BuildDelay();
	void SpawnBuildGhost();
	void BuildCycle();
	void GiveBuildColor(bool isGreen);
	void LaunchBuildMode();
	void StopBuildMode();
	void GetDataTableRowNames();
	void ChangeMesh();
	void SpawnBuild();

	bool LocalFound = false;
	FBuildDetectResult DetectBuildBox();
};

