// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "GameFramework/Actor.h"
#include "Agents.h"
#include "PlanTest.generated.h"

UCLASS()
class TOOLMAN_API APlanTest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlanTest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite)
	AAgents* Agents;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="MyPaintingPoints")
	TArray<FVector> PaintPoints;

	int time = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="MyPaintingPoints")
	bool SimFinished;
};
