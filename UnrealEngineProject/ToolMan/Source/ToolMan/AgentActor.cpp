// Fill out your copyright notice in the Description page of Project Settings.


#include "AgentActor.h"

// Sets default values
AAgentActor::AAgentActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	// RootComponent = SphereComponent;
	// SphereComponent->InitSphereRadius(1.0f);
	// // SphereComponent->SetCollisionProfileName(TEXT("Pawn"));
	//
	// VisualComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualComponent"));
	// VisualComponent->SetupAttachment(RootComponent);
	// static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("StaticMesh'/Game/Meshes/StaticMesh.StaticMesh'"));
	// if (SphereVisualAsset.Succeeded())
	// {
	// 	VisualComponent->SetStaticMesh(SphereVisualAsset.Object);
	// 	VisualComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	//
	// 	static ConstructorHelpers::FObjectFinder<UMaterialInstance> MatInstObj000(TEXT("MaterialInstanceConstant'/Game/AutomotiveMaterials/Materials/Exterior/Lights/MI_Lamp_White.MI_Lamp_White'"));
	// 	MaterialInstances.Add(MatInstObj000.Object);
	// 	static ConstructorHelpers::FObjectFinder<UMaterialInstance> MatInstObj00(TEXT("MaterialInstanceConstant'/Game/AutomotiveMaterials/Materials/Exterior/Lights/MI_Transparent_Cover_Tinted.MI_Transparent_Cover_Tinted'"));
	// 	MaterialInstances.Add(MatInstObj00.Object);
	// 	static ConstructorHelpers::FObjectFinder<UMaterialInstance> MatInstObj0(TEXT("MaterialInstanceConstant'/Game/AutomotiveMaterials/Materials/Exterior/Lights/MI_Tint_Red.MI_Tint_Red'"));
	// 	MaterialInstances.Add(MatInstObj0.Object);
	// 	static ConstructorHelpers::FObjectFinder<UMaterialInstance> MatInstObj1(TEXT("MaterialInstanceConstant'/Game/AutomotiveMaterials/Materials/Exterior/CarPaint/MI_CarPaint_Mix_01.MI_CarPaint_Mix_01'"));
	// 	MaterialInstances.Add(MatInstObj1.Object);
	// 	static ConstructorHelpers::FObjectFinder<UMaterialInstance> MatInstObj2(TEXT("MaterialInstanceConstant'/Game/AutomotiveMaterials/Materials/Exterior/CarPaint/MI_CarPaint_Mix_02.MI_CarPaint_Mix_02'"));
	// 	MaterialInstances.Add(MatInstObj2.Object);
	// 	static ConstructorHelpers::FObjectFinder<UMaterialInstance> MatInstObj3(TEXT("MaterialInstanceConstant'/Game/AutomotiveMaterials/Materials/Exterior/CarPaint/MI_CarPaint_Mix_03.MI_CarPaint_Mix_03'"));
	// 	MaterialInstances.Add(MatInstObj3.Object);
	//
	// 	VisualComponent->SetMaterial(0, MaterialInstances[0]);
	//
	// 	// SphereColor = CreateDefaultSubobject<UPointLightComponent>(TEXT("SphereColor"));
	// 	// SphereColor->SetupAttachment(SphereVisual);
	// }

}

// Called when the game starts or when spawned
void AAgentActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAgentActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

