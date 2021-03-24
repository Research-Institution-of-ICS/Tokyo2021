// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "GameFramework/Actor.h"
#include "Dom/JsonObject.h"
#include "Misc/FileHelper.h"
#include "Serialization/JsonReader.h"
#include "EngineUtils.h"
#include "GameFramework/DefaultPawn.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/PlayerController.h"
#include "Cameraline.h"
#include "PlaceActor.h"
#include "Agents.h"

#include "MapMananger.generated.h"




UCLASS()
class TOOLMAN_API AMapMananger : public AActor
{
	GENERATED_BODY()
	
	public:	
	// Sets default values for this actor's properties
	AMapMananger();

	UPROPERTY()
	UFloatingPawnMovement* ToolPawnMovement;
	
	UPROPERTY()
	TMap<FString, APlaceActor*> Places;

	UPROPERTY()
	TArray<FString> Info;
	
	UPROPERTY(BlueprintReadWrite)
	bool IsReady = false;

	UPROPERTY(BlueprintReadWrite)
	AAgents* Agents;
	ACameraline* Default;
	UPROPERTY()
	int TickCount = 0;

	void GetAndSetToolPawnMovement();

	UFUNCTION(BlueprintCallable)
    void GetPlaces();

	UFUNCTION(BlueprintCallable)
    void GetPerson();

	UFUNCTION(BlueprintCallable)
    void GetRoutes();


	void WriteResult();
	void WriteTempResult(FString FileName);

	protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FString LoadFilePathStr;
	FString ResultFilePathStr;
};
