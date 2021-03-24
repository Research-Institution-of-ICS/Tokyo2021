// Fill out your copyright notice in the Description page of Project Settings.


#include "SIOActor.h"

#include "Engine/Engine.h"

// Sets default values
ASIOActor::ASIOActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = SphereComponent;
	SphereComponent->InitSphereRadius(40.0f);
	// SphereComponent->SetCollisionProfileName(TEXT("Pawn"));

	VisualComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualComponent"));
	VisualComponent->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> VisualAsset(TEXT("/Game/Resources/PolygonPrototype/Meshes/Props/SM_Prop_Crate_Exclamation_01.SM_Prop_Crate_Exclamation_01"));
	if (VisualAsset.Succeeded())
	{
		VisualComponent->SetStaticMesh(VisualAsset.Object);
		VisualComponent->AddRelativeLocation(FVector(0, 0, 0));
		VisualComponent->SetWorldScale3D(FVector(1));
	}
	
	SIOClientComponent = CreateDefaultSubobject<USocketIOClientComponent>(TEXT("SocketIOClientComponent"));
	SIOClientComponent->AddressAndPort = TEXT("http://127.0.0.1:2333");
	
}

void ASIOActor::Reset()
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
	TArray<TSharedPtr<FJsonValue>> Array;
	int NewObservation = 2;
	Array.Add(MakeShareable(new FJsonValueNumber(NewObservation)));
	VisualComponent->SetWorldLocation(FVector(NewObservation*100-200, 0, 0));
	JsonObject->SetArrayField(TEXT("observation"), Array);
	SIOClientComponent->EmitNative(TEXT("reset"), JsonObject);
}

void ASIOActor::Act(TArray<TSharedPtr<FJsonValue>> ObservationLast, int32 Action)
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
	TArray<TSharedPtr<FJsonValue>> Array;
	int NewObservation;
	float Reward;
	bool Done;
	if (Action == 0)
	{
		NewObservation = ObservationLast[0]->AsNumber()-1;
		
	} else
	{
		NewObservation = ObservationLast[0]->AsNumber()+1;
	}
	if (NewObservation <= 0)
	{
		Reward = -1;
		Done = true;
	} else if (NewObservation >= 4)
	{
		Reward = 1;
		Done = true;
	} else
	{
		Reward = 0;
		Done = false;
	}
	Array.Add(MakeShareable(new FJsonValueNumber(NewObservation)));
	VisualComponent->SetWorldLocation(FVector(NewObservation*100-200, 0, 0));
	JsonObject->SetArrayField(TEXT("observation"), Array);
	JsonObject->SetNumberField(TEXT("reward"), Reward);
	JsonObject->SetBoolField(TEXT("done"), Done);
	JsonObject->SetStringField(TEXT("info"), "");
	SIOClientComponent->EmitNative(TEXT("step"), JsonObject);
}

// Called when the game starts or when spawned
void ASIOActor::BeginPlay()
{
	Super::BeginPlay();
	
	Reset();

	SIOClientComponent->OnNativeEvent(TEXT("act"), [this](const FString& Event, const TSharedPtr<FJsonValue>& Message)
    {
		TSharedPtr<FJsonObject> JsonNode = Message->AsObject();
		TArray<TSharedPtr<FJsonValue>> ObservationLast = JsonNode->GetArrayField("observation_last");
		int32 Action = JsonNode->GetIntegerField("action");
		if (Action == -1)
		{
			Reset();
		} else
		{
			Act(ObservationLast, Action);
			GEngine->AddOnScreenDebugMessage(-1, 2.33f, FColor::Red, *USIOJConvert::ToJsonString(JsonNode->GetObjectField("logging")));
		}
    });
	

}

// Called every frame
void ASIOActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

