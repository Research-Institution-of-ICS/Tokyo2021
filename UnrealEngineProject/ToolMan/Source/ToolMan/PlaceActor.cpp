// Fill out your copyright notice in the Description page of Project Settings.


#include "PlaceActor.h"




// Sets default values
APlaceActor::APlaceActor()
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
		VisualComponent->AddRelativeLocation(FVector(0, 0, 23333));
		VisualComponent->SetWorldScale3D(FVector(100));
	}
}

// Called when the game starts or when spawned
void APlaceActor::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void APlaceActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	VisualComponent->AddLocalRotation(FRotator(0, 1, 0));

}

