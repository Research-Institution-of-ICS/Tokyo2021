// Fill out your copyright notice in the Description page of Project Settings.


#include "Spline.h"

// Sets default values
ASpline::ASpline()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MySpline = CreateDefaultSubobject<USplineComponent>(FName("MySpline"));
	SplineForward = ESplineMeshAxis::Type::X;
	Mesh = nullptr;



}

// Called when the game starts or when spawned
void ASpline::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ASpline::OnConstruction(const FTransform& Transform)
{
	SetupSpline();
}

void ASpline::SetupSpline()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "called in setup spline");
	if (Mesh == nullptr) 
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "has a static mesh");
		UWorld* World = this->GetWorld();
		for (int32 i = 0; i < (MySpline->GetNumberOfSplinePoints() - 2); i++)
		{
			USplineMeshComponent* SplineMesh = NewObject<USplineMeshComponent>(this, USplineMeshComponent::StaticClass());
			SplineMesh->SetStaticMesh(Mesh);
			SplineMesh->SetCollisionProfileName(TEXT("BlockAll"));
			SplineMesh->RegisterComponentWithWorld(World);
			SplineMesh->CreationMethod = EComponentCreationMethod::UserConstructionScript;
			SplineMesh->SetMobility(EComponentMobility::Movable);
			SplineMesh->SetForwardAxis(SplineForward, true);
			SplineMesh->AttachToComponent(MySpline, FAttachmentTransformRules::KeepRelativeTransform);
			FVector SP = MySpline->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::Type::Local);
			FVector ST = MySpline->GetTangentAtSplinePoint(i, ESplineCoordinateSpace::Type::Local);
			FVector EP = MySpline->GetLocationAtSplinePoint(i + 1, ESplineCoordinateSpace::Type::Local);
			FVector ET = MySpline->GetTangentAtSplinePoint(i + 1, ESplineCoordinateSpace::Type::Local);
			SplineMesh->SetStartAndEnd(SP, ST, EP, ET, true);
			SplineMesh->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
		}
	}
}

