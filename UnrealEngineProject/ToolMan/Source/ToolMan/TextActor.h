// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Text3DComponent.h"
#include "Text3D/Public/Text3DActor.h"
#include "TextActor.generated.h"


UCLASS()
class TOOLMAN_API ATextActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATextActor();

	void SpawnText3D(int Index, FVector Location, FRotator Rotation, FVector Scale);
	TMap<FString, UText3DComponent*> Text3Ds;
	TArray<FVector>Locations;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
