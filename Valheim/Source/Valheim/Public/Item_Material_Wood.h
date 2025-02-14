// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Item_Material_Wood.generated.h"

UCLASS()
class VALHEIM_API AItem_Material_Wood : public AItem
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem_Material_Wood();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
