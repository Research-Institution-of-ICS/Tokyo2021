// Fill out your copyright notice in the Description page of Project Settings.


#include "Cameraline.h"

#include "RenderGraphUtils.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACameraline::ACameraline()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACameraline::BeginPlay()
{
	Super::BeginPlay();
	////////////////////////////////////////////////////////////////////////////////////
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->bShowMouseCursor = true;
	PlayerController->SetControlRotation(FRotator(0));
	GetDefaultPawn();
	////////////////////////////////////////////////////////////////////////////////////
	
	SplinePoints.Add(FVector (11891,-142417,1785575));
	//SplinePoints.Add(FVector (-236279,-179555,1705203));
	// SplinePoints.Add(FVector (-119950,144471,439977));
	// SplinePoints.Add(FVector (360173,881102,460184));
	// SplinePoints.Add(FVector (5272,339708,237003));
	// SplinePoints.Add(FVector (-448655,32962,126872));
	// SplinePoints.Add(FVector (836830,45509,68369));
	// SplinePoints.Add(FVector (-1027922,-264857,109394));
	// SplinePoints.Add(FVector (-485351,-350111,67633));
	// SplinePoints.Add(FVector (251333,19552,587188));
	// SplinePoints.Add(FVector (-448655,32962,126872));
	
	FVector Location(0);
	FRotator Rotation(0.f);
	FVector Scale(1);
	FTransform SpawnTransform = FTransform(Rotation, Location, Scale);
	PSplineActor = GetWorld()->SpawnActorDeferred<ASpline>(ASpline::StaticClass(),SpawnTransform);
	PSplineActor->MySpline->SetSplineLocalPoints(SplinePoints);

	Location = PSplineActor->MySpline->GetLocationAtDistanceAlongSpline(DistanceMoved, ESplineCoordinateSpace::World);
	Rotation =  FRotator(-90.0f,90.f,180.0f);
	DefaultPawn->SetActorLocation(Location);
	PlayerController->SetControlRotation(Rotation);
	
	
}

// Called every frame
void ACameraline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	// auto Location = PSplineActor->MySpline->GetLocationAtDistanceAlongSpline(DistanceMoved, ESplineCoordinateSpace::World);
	// auto Rotation = PSplineActor->MySpline->GetRotationAtDistanceAlongSpline(DistanceMoved, ESplineCoordinateSpace::Local);
	// DefaultPawn->SetActorLocation(Location);
	// PlayerController->SetControlRotation(Rotation);
	// PlayerController->SetControlRotation(FRotator(-180,-90,90));
	// DistanceMoved += PSplineActor->MySpline->GetSplineLength()*0.001f;
}

void ACameraline::GetDefaultPawn()
{
	for (TActorIterator<ADefaultPawn> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		DefaultPawn = *ActorItr;		
		break;
	}
}

