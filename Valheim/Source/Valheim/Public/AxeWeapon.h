// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AxeWeapon.generated.h"

UCLASS()
class VALHEIM_API AAxeWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAxeWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


// 무기 충돌 컴프
UPROPERTY(VisibleAnywhere, Category = Collision)
class USphereComponent* collisionComp;

// 무기 외관 컴프
UPROPERTY(VisibleAnywhere, Category=AxeMesh)
class UStaticMeshComponent* AxeComp;

UFUNCTION()
void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
