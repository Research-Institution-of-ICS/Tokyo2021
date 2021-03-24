// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "SocketIOClientComponent.h"
#include "GameFramework/Actor.h"
#include "SIOActor.generated.h"

UCLASS()
class TOOLMAN_API ASIOActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASIOActor();

	UStaticMeshComponent* VisualComponent;
	USocketIOClientComponent* SIOClientComponent;

	void Reset();
	void Act(TArray<TSharedPtr<FJsonValue>> ObservationLast, int32 Action);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
