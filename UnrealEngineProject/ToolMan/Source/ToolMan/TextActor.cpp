// Fill out your copyright notice in the Description page of Project Settings.


#include "TextActor.h"

// Sets default values
ATextActor::ATextActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATextActor::SpawnText3D(int Index, FVector Location, FRotator Rotation, FVector Scale)
{
	UClass* TextBlueprint = LoadClass<AText3DActor>(NULL, TEXT("Blueprint'/Game/Blueprints/Text3DActor_Blueprint_2.Text3DActor_Blueprint_2_C'"));
	Location.Z += 0;
	AText3DActor* Text3DActor = GetWorld()->SpawnActor<AText3DActor>(TextBlueprint, Location, FRotator(-60, -90, 0));
	Text3DActor->GetText3DComponent()->SetVisibility(true);
	Text3DActor->GetText3DComponent()->SetWorldScale3D(FVector(6));
	Text3DActor->GetText3DComponent()->SetText(FText::FromString(TEXT("laji?????")));
	// TArray<UText3DComponent*> MyText3DComponents;
	// Text3DActor->GetComponents(MyText3DComponents);
	// Text3Ds.Add(FString::FromInt(Index), MyText3DComponents[0]);
	
	
}

// Called when the game starts or when spawned
void ATextActor::BeginPlay()
{
	Super::BeginPlay();
	for (int i = 0; i < 1000; ++i)
	{
		FVector Location;
		Location = FVector(FMath::RandRange(0.f,1.f)*10000,FMath::RandRange(0.f,1.f)*10000,233333.0);
		Locations.Add(Location);
		SpawnText3D(i, Location, FRotator(-60, -90, 0), FVector(60));
	}
	// for (auto Text3D : Text3Ds)
	// {
	// 	Text3D.Value->SetText(FText::FromString("sadasfg"));
	// }
	//
	
}

// Called every frame
void ATextActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

