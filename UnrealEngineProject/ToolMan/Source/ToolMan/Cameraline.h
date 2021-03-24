// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spline.h"
#include "EngineUtils.h"
#include "GameFramework/DefaultPawn.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Cameraline.generated.h"

UCLASS()
class TOOLMAN_API ACameraline : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraline();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	TArray<FVector>SplinePoints;
	void GetDefaultPawn();
	ADefaultPawn* DefaultPawn;

	ASpline* PSplineActor;
	APlayerController* PlayerController;

	float DistanceMoved = 0.f;
};
