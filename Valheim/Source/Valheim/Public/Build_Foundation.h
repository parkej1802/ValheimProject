#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Components/BoxComponent.h"
#include "BuildInterface.h"
#include "S_Buildables.h"
#include "Components/StaticMeshComponent.h"
#include "Build_Foundation.generated.h"

UCLASS()
class VALHEIM_API ABuild_Foundation : public AStaticMeshActor, public IBuildInterface
{
	GENERATED_BODY()
	
public:
	ABuild_Foundation();

	void SetFoundationMesh();

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	class UBoxComponent* BoxComp1;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	class UBoxComponent* BoxComp2;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	class UBoxComponent* BoxComp3;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	class UBoxComponent* BoxComp4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* Wall1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* Wall2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* Wall3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* Wall4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* Floor;

	TArray<UBoxComponent*> BoxCompArray;

	virtual TArray<UBoxComponent*> GetBoxCollision_Implementation() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Data)
    TArray<FBuildingStruct> BuildableDataArray;
};
