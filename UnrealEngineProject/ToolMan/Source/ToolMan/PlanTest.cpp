// Fill out your copyright notice in the Description page of Project Settings.


#include "PlanTest.h"

// Sets default values
APlanTest::APlanTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlanTest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlanTest::Tick(float DeltaTime)
{
//	Super::Tick(DeltaTime);
//
//	time += 1;
//	
//	if (time > 1000)
//	{
//		PaintPoints = Agents->PaintingPoints;
//
//		if (Agents->SimSeconds > 100000)
//		{
//			SimFinished = true;
//		}
//	}
}