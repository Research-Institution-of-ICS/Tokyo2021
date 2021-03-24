// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "Spline.generated.h"

UCLASS()
class TOOLMAN_API ASpline : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpline();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void OnConstruction(const FTransform& Transform) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USplineComponent* MySpline;
 
	UPROPERTY(EditAnywhere)
	TEnumAsByte<ESplineMeshAxis::Type> SplineForward;
	//int splineForward;
	TArray<FVector>SplinePoints;

	UPROPERTY(EditAnywhere)
	UStaticMesh* Mesh;
    
	void SetupSpline();

};
