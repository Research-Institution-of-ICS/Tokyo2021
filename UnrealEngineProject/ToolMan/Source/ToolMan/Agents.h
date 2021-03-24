// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "SocketIOClientComponent.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/Actor.h"
#include "AgentActor.h"
#include "UObject/ObjectMacros.h"

#include "Agents.generated.h"


USTRUCT(BlueprintType)
struct FPlace
{
	GENERATED_USTRUCT_BODY()

    UPROPERTY()
    FVector Location = FVector(0);
	
	UPROPERTY()
    FString Name = "";

	UPROPERTY()
    FString Address = "";
};


USTRUCT(BlueprintType)
struct FSection
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
    FVector Location1 = FVector(0);
	
	UPROPERTY()
    FVector Location2 = FVector(0);
	
	UPROPERTY()
    float Distance = 0;

	UPROPERTY()
	int GridIndex = 0;
};


USTRUCT(BlueprintType)
struct FAction
{
	GENERATED_USTRUCT_BODY()

    UPROPERTY()
    FString Action = "";

	UPROPERTY()
    FString CurrentPlace = "";
	
	UPROPERTY()
    FString TargetPlace = "";
};



USTRUCT(BlueprintType)
struct FAgent
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
    FString Game = "";

	UPROPERTY()
	TArray<FAction> Actions;

	UPROPERTY()
    TArray<FAction> ActionsBackup;

	UPROPERTY()
	int ActionIndex = 0;

	UPROPERTY()
    FString Country = "";
	
	UPROPERTY()
    int InstanceIndex = 0;

	UPROPERTY()
    int GridIndex = 0;

	UPROPERTY()
    float InfectionNum = 0.f;

	UPROPERTY()
	FVector Location = FVector(0);

	UPROPERTY()
    FRotator Rotation = FRotator(0);

	UPROPERTY()
    FVector Scale = FVector(1);

	UPROPERTY()
    FTransform Transform = FTransform(FRotator(0), FVector(0), FVector(1));
	
	UPROPERTY()
	TArray<FSection> Route;

	UPROPERTY()
	int SectionIndex = 0;

	UPROPERTY()
	float SectionRate = 0;
	
	UPROPERTY()
    FString Type = "";

	UPROPERTY()
    bool InHospital = false;

	UPROPERTY()
    float SectionRateBias = FMath::RandRange(0.f, 0.0233f);
	
	UPROPERTY()
	int SectionIndexBias = 0;

	UPROPERTY()
    int Num = 1;

	UPROPERTY()
	FString StateOfHealth = "Healthy";

	UPROPERTY()
	bool IsFirstClass = false;

	UPROPERTY()
    FString ChangingMethod = "";
};

USTRUCT(BlueprintType)
struct FGrid
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "MyGrids")
	FVector GridBottomLeft;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "MyGrids")
    FVector GridUpperRight;

	UPROPERTY()
    FVector GridCenter;

	UPROPERTY()
    int XIndex = 0;

	UPROPERTY()
	int YIndex = 0;

	UPROPERTY()
	float P = 0.f;

	UPROPERTY()
    float InfectionNum = 0.f;

    UPROPERTY()
    int HealthyNum = 0;

	UPROPERTY()
	int NewIncubationNum = 0;
	
	UPROPERTY()
	int IncubationNum = 0;

	UPROPERTY()
	int Onset1Num = 0;

	UPROPERTY()
	int Onset2Num = 0;

	UPROPERTY()
	int Onset3Num = 0;

	UPROPERTY()
	int DeadNum = 0;

	UPROPERTY()
	int RecoveredNum = 0;

	UPROPERTY()
	int HealthyNumTemp = 0;

	UPROPERTY()
    int IncubationNumTemp = 0;

	UPROPERTY()
    int Onset1NumTemp = 0;

	UPROPERTY()
    int Onset2NumTemp = 0;

	UPROPERTY()
    int Onset3NumTemp = 0;

	UPROPERTY()
    int DeadNumTemp = 0;

	UPROPERTY()
    int RecoveredNumTemp = 0;
};

USTRUCT(BlueprintType)
struct FStatistic
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
    float R = 0.f;
	
	UPROPERTY()
    int HealthyNum = 0;

	UPROPERTY()
    int IncubationNum = 0;

	UPROPERTY()
    int Onset1Num = 0;

	UPROPERTY()
    int Onset2Num = 0;

	UPROPERTY()
    int Onset3Num = 0;

	UPROPERTY()
    int DeadNum = 0;

	UPROPERTY()
    int RecoveredNum = 0;

	UPROPERTY()
    int TotalNum = 0;

	UPROPERTY()
	int GameNum = 0;

	UPROPERTY()
	int TotalAction = 0;

	UPROPERTY()
	int IncubationNum0 = 0;

	float GridIncubationDay = 0;

	UPROPERTY()
	FString Info = "";
	
	UPROPERTY()
	FString GameInfo = "";
};

UCLASS()
class TOOLMAN_API AAgents : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAgents();

	UPROPERTY(BlueprintReadWrite)
	TArray<int> Observation;


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	UFUNCTION(BlueprintCallable)
	void UpdateAgentsTransform();

	UFUNCTION(BlueprintCallable)
	void UpdateAgentsHealth();

	UFUNCTION(BlueprintCallable)
    void UpdateAgentsActions();

    void UpdateAgentsInstanceTransform(FString Type);

	void InitializeAgentState(FAgent& Agent, FString Type);

	void RandomMoveAgent(FAgent& Agent, FVector Center, float Radius1, float Radius2);

	void ChangeActions(FAgent& Agent, FString Method);

	void InitGrids();
	
	int GetGridIndex(FVector Location);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	FVector AgentScaleNormal = FVector(1);
	FVector AgentScaleBackground = FVector(1);
	FVector BottomLeft = FVector(-1494228.06, 1223263.16, 0);
	FVector UpperRight = FVector(1490115.5, -1225768.89, 0);

    int GridSize = 1000;
	
	int SecondsPerTick = 600;

    int SimSeconds = 0;

    int UpdateAgentsTransformSeconds = 0;
	
    int UpdateAgentsHealthSeconds = 0;

	int SimHoursRecord = 0;

	int AgentNum = 0;

	int InitIncubationNum = 1000;

	float IncubationInfectionRate = 0.000015f;

	float OnsetInfectionRate = 0.001f;

    float DeathRate = 0.05f;
	
	TMap<FString, FAgent> Agents;
	UPROPERTY(BlueprintReadOnly)
		TArray<FGrid> Grids;
	TArray<FVector> Buildings;
	TMap<FString, FPlace> Places;
	TArray<FString> VenueIDList;
	TArray<FString> HospitalIDList;
	TArray<FString> AirportIDList;
	TArray<FString> PlaceIDList;
	TMap<FString, TArray<FSection>> Routes;
	TMap<FString, TArray<FSection>> Routes1;
	TMap<FString, TArray<FSection>> Routes2;
	TMap<FString, TArray<FSection>> Routes3;

	FStatistic Statistic;
	TMap<FString, FStatistic> Statistics;

	TMap<FString, UHierarchicalInstancedStaticMeshComponent*> HISMC;

	USocketIOClientComponent* SIOClientComponent;

	void Reset();
	void Act();

	int GameNum = 0;

	int TotalAction = 0;

	FString GameInfo;

	int ActionReceived = 0;

	bool IsDone = false;

	FString Logging;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	TMap<FVector, int32> InfectionNumberMapToGridVectorForPaintingPoints;
	
};

inline int AAgents::GetGridIndex(FVector Location)
{
	int Index;
	if (-100 < Location.Z && Location.Z < 10)
	{
		Index = FMath::FloorToInt((Location.X-BottomLeft.X)/(UpperRight.X-BottomLeft.X)*GridSize)*GridSize+FMath::FloorToInt((Location.Y-BottomLeft.Y)/(UpperRight.Y-BottomLeft.Y)*GridSize);
	} else if (Location.Z >= 10)
	{
		Index = GridSize*GridSize+GridSize+FMath::FloorToInt((Location.X-BottomLeft.X)/(UpperRight.X-BottomLeft.X)*GridSize)*GridSize+FMath::FloorToInt((Location.Y-BottomLeft.Y)/(UpperRight.Y-BottomLeft.Y)*GridSize);
	} else
	{
		Index = -1000;
	}
	return Index;
}
