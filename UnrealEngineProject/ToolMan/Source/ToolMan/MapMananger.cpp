// Fill out your copyright notice in the Description page of Project Settings.


#include "MapMananger.h"



// Sets default values
AMapMananger::AMapMananger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

// Called when the game starts or when spawned
void AMapMananger::BeginPlay()
{
	Super::BeginPlay();

	GetAndSetToolPawnMovement();
	// Agents = GetWorld()->SpawnActor<AAgents>();
	// GetPlaces();
	// GetRoutes();
	// GetPerson();
}

void AMapMananger::GetAndSetToolPawnMovement()
{
	for (TActorIterator<ADefaultPawn> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		ADefaultPawn* Actor = *ActorItr;
		
		
		TArray<UFloatingPawnMovement*> FloatingPawnMovement;
		Actor->GetComponents(FloatingPawnMovement);
		ToolPawnMovement = FloatingPawnMovement[0];
		ToolPawnMovement->MaxSpeed = 66666.f;
		ToolPawnMovement->Acceleration = 23333.f;
		ToolPawnMovement->Deceleration = 23333.f;
		break;
	}
}

void AMapMananger::GetPlaces()
{
	FString FilePath = FPaths::ProjectDir() + TEXT("Data/Places.json");
	if (FPaths::FileExists(FilePath))
	{
		FString FileStr;
		FFileHelper::LoadFileToString(FileStr, *FilePath);
		TArray<TSharedPtr<FJsonValue>> JsonArray;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(FileStr);
		GEngine->AddOnScreenDebugMessage(-1, 2.33f, FColor::Black, FileStr);
		if (FJsonSerializer::Deserialize(Reader, JsonArray))
		{
			for (auto JsonValue : JsonArray)
			{
				auto JsonNode = JsonValue->AsObject();
				
				APlaceActor* PlaceActor = GetWorld()->SpawnActor<APlaceActor>();
				PlaceActor->SetActorLocation(FVector(JsonNode->GetNumberField("x"), JsonNode->GetNumberField("y"), 0));
				Places.Add(JsonNode->GetStringField("name"), PlaceActor);

				FPlace Place;
				Place.Location = FVector(JsonNode->GetNumberField("x"), JsonNode->GetNumberField("y"), 0);
				Place.Name = JsonNode->GetStringField("name");
				Place.Address = JsonNode->GetStringField("address");
				Agents->Places.Add(JsonNode->GetStringField("id"), Place);
				if (JsonNode->GetStringField("type") == "Venue")
				{
					Agents->VenueIDList.Add(JsonNode->GetStringField("id"));
				}
				if (JsonNode->GetStringField("type") == "Hospital")
				{
					Agents->HospitalIDList.Add(JsonNode->GetStringField("id"));
				}
				if (JsonNode->GetStringField("type") == "Airport")
				{
					Agents->AirportIDList.Add(JsonNode->GetStringField("id"));
				}
				Agents->PlaceIDList.Add(JsonNode->GetStringField("id"));
			}
		}
	}
	FilePath = FPaths::ProjectDir() + TEXT("Data/Info1.json");
	if (FPaths::FileExists(FilePath))
	{
		FString FileStr;
		FFileHelper::LoadFileToString(FileStr, *FilePath);
		TArray<TSharedPtr<FJsonValue>> JsonArray;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(FileStr);
		if (FJsonSerializer::Deserialize(Reader, JsonArray))
		{
			for (auto JsonValue : JsonArray)
			{
				auto JsonNode = JsonValue->AsString();
				Info.Add(JsonNode);
			}
		}
	}
	FilePath = FPaths::ProjectDir() + TEXT("Data/Buildings.json");
	if (FPaths::FileExists(FilePath))
	{
		FString FileStr;
		FFileHelper::LoadFileToString(FileStr, *FilePath);
		TArray<TSharedPtr<FJsonValue>> JsonArray;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(FileStr);
		if (FJsonSerializer::Deserialize(Reader, JsonArray))
		{
			for (auto JsonValue : JsonArray)
			{
				auto JsonNode = JsonValue->AsArray();
				Agents->Buildings.Add(FVector(JsonNode[0]->AsNumber(), JsonNode[1]->AsNumber(), JsonNode[2]->AsNumber()));
			}
		}
	}
	Agents->InitGrids();
}

void AMapMananger::GetRoutes()
{
	FString FilePath = FPaths::ProjectDir() + TEXT("Data/Routes.json");
	if (FPaths::FileExists(FilePath))
	{
		FString FileStr;
		FFileHelper::LoadFileToString(FileStr, *FilePath);
		TSharedPtr<FJsonObject> JsonObject;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(FileStr);

		if (FJsonSerializer::Deserialize(Reader, JsonObject))
		{
			for (auto Value : JsonObject->Values)
			{
				TArray<FVector> RouteLocations;
				for (auto ArrayField : Value.Value->AsArray())
				{
					auto LocationArray = ArrayField->AsArray();
					FVector Location = FVector(LocationArray[0]->AsNumber(), LocationArray[1]->AsNumber(), LocationArray[2]->AsNumber());
					RouteLocations.Add(Location);
				}
				TArray<FSection> Sections;
				TArray<FSection> Sections1;
				TArray<FSection> Sections2;
				TArray<FSection> Sections3;
				for (int i = 0; i < 1; i ++)
				{
					FSection Section;
					Section.Location1 = RouteLocations[i];
					Section.Location2 = RouteLocations[i+1];
					Section.Distance = FVector::Distance(Section.Location1, Section.Location2);
					Section.GridIndex = Agents->GetGridIndex((Section.Location1+Section.Location2)/2);
					Sections1.Add(Section);
					Sections.Add(Section);
				}
				Agents->Routes1.Add(Value.Key, Sections1);
				for (int i = 1; i < RouteLocations.Num()-2; i ++)
				{
					FSection Section;
					Section.Location1 = RouteLocations[i];
					Section.Location2 = RouteLocations[i+1];
					Section.Distance = FVector::Distance(Section.Location1, Section.Location2);
					Section.GridIndex = Agents->GetGridIndex((Section.Location1+Section.Location2)/2);
					Sections2.Add(Section);
					Sections.Add(Section);
				}
				Agents->Routes2.Add(Value.Key, Sections2);
				for (int i = RouteLocations.Num()-2; i < RouteLocations.Num()-1; i ++)
				{
					FSection Section;
					Section.Location1 = RouteLocations[i];
					Section.Location2 = RouteLocations[i+1];
					Section.Distance = FVector::Distance(Section.Location1, Section.Location2);
					Section.GridIndex = Agents->GetGridIndex((Section.Location1+Section.Location2)/2);
					Sections3.Add(Section);
					Sections.Add(Section);
				}
				Agents->Routes3.Add(Value.Key, Sections3);
				Agents->Routes.Add(Value.Key, Sections);
			}
		}
	}
}

void AMapMananger::GetPerson()
{
	FString FilePath = FPaths::ProjectDir() + TEXT("Data/FileName.json");

	if (FPaths::FileExists(FilePath))
	{
		FString FileStr;
		FFileHelper::LoadFileToString(FileStr, *FilePath);
		TArray<TSharedPtr<FJsonValue>> JsonArray;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(FileStr);
		if (FJsonSerializer::Deserialize(Reader, JsonArray))
		{
			LoadFilePathStr = JsonArray[0]->AsString();
			ResultFilePathStr = JsonArray[1]->AsString();
		}
	}


	FilePath = FPaths::ProjectDir() + LoadFilePathStr;
	if (FPaths::FileExists(FilePath))
	{
		FString FileStr;
		FFileHelper::LoadFileToString(FileStr, *FilePath);
		TArray<TSharedPtr<FJsonValue>> JsonArray;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(FileStr);
		if (FJsonSerializer::Deserialize(Reader, JsonArray))
		{
			int IncubationNum = 0;
			for (auto JsonValue : JsonArray)
			{
				auto JsonNode = JsonValue->AsObject();
				// GEngine->AddOnScreenDebugMessage(-1, 2.33f, FColor::Black, JsonNode->GetStringField("id"));

				FAgent PlayerAgent;
				PlayerAgent.Game = JsonNode->GetStringField("game");
				PlayerAgent.Country = JsonNode->GetStringField("country");
				TArray<FAction> Actions;
				for (auto ArrayField : JsonNode->GetArrayField("action"))
				{
					FAction Action;
					Action.Action = ArrayField->AsArray()[0]->AsString();
					Action.CurrentPlace = ArrayField->AsArray()[1]->AsString();
					Action.TargetPlace = ArrayField->AsArray()[2]->AsString();
					if (Action.Action != "yidong" && Action.CurrentPlace != Action.TargetPlace)
					{
						Action.Action = "yidong";
					}
					Actions.Add(Action);
				}
				Actions[0].CurrentPlace = Actions[0].TargetPlace;
				PlayerAgent.Actions = Actions;
				PlayerAgent.ActionsBackup = Actions;
				if (FMath::RandRange(0.f, 1.f) < 0.1f && IncubationNum < Agents->InitIncubationNum)
				{
					PlayerAgent.StateOfHealth = "Incubation";
					PlayerAgent.IsFirstClass = true;
					IncubationNum += 1;
				}
				Agents->InitializeAgentState(PlayerAgent,"Player");
				Agents->Agents.Add(JsonNode->GetStringField("id")+"_Player", PlayerAgent);

				FAgent AudiencePlayer;
				TArray<FAction> AudienceActions;
				FString RandomPlace = FString::FromInt(FMath::RandRange(100, 199));
				for (int i = 0; i < Actions.Num(); i++)
				{
					FAction AudienceAction;
					auto Action = Actions[i];
					if (Action.Action == "bisai")
					{
						AudienceAction.Action = "bisai";
						AudienceAction.CurrentPlace = Action.CurrentPlace;
						AudienceAction.TargetPlace = Action.CurrentPlace;
					} else if (Action.Action == "yidong"){
						if (i < Actions.Num()-1)
						{
							if (Action.Action == "yidong" && Actions[i+1].Action == "bisai")
							{
								AudienceAction.Action = "yidong";
								AudienceAction.CurrentPlace = RandomPlace;
								AudienceAction.TargetPlace = Action.TargetPlace;
							}
						}
						if (Action.Action == "yidong" && Actions[i-1].Action == "bisai")
						{
							AudienceAction.Action = "yidong";
							AudienceAction.CurrentPlace = Action.CurrentPlace;
							AudienceAction.TargetPlace = RandomPlace;
						}
					} else
					{
						AudienceAction.Action = "shuijiao";
						AudienceAction.CurrentPlace = RandomPlace;
						AudienceAction.TargetPlace = RandomPlace;
					}
					AudienceActions.Add(AudienceAction);
				}
				AudiencePlayer.Num = 10;
				AudiencePlayer.Actions = AudienceActions;
				AudiencePlayer.ActionsBackup = AudienceActions;
				Agents->InitializeAgentState(AudiencePlayer,"Audience");
				Agents->Agents.Add(JsonNode->GetStringField("id")+"_Audience", AudiencePlayer);


				FAgent StaffPlayer;
				TArray<FAction> StaffActions;
				for (int i = 0; i < Actions.Num(); i++)
				{
					FAction StaffAction;
					auto Action = Actions[i];
					StaffAction = Action;
					StaffActions.Add(StaffAction);
				}
				StaffPlayer.Num = 3;
				StaffPlayer.Actions = StaffActions;
				StaffPlayer.ActionsBackup = StaffActions;
				Agents->InitializeAgentState(StaffPlayer,"Staff");
				Agents->Agents.Add(JsonNode->GetStringField("id")+"_Staff", StaffPlayer);

				FAgent BackgroundPlayer;
				TArray<FAction> BackgroundActions;
				FString FromPlace = Agents->PlaceIDList[FMath::RandRange(0, Agents->PlaceIDList.Num()-1)];
				FString ToPlace = Agents->PlaceIDList[FMath::RandRange(0, Agents->PlaceIDList.Num()-1)];
				while (ToPlace == FromPlace)
				{
					ToPlace = Agents->PlaceIDList[FMath::RandRange(0, Agents->PlaceIDList.Num()-1)];
				}
				for (int i = 0; i < Actions.Num(); i++)
				{
					FAction BackgroundAction;
					BackgroundAction.Action = "yidong";
					BackgroundAction.CurrentPlace = FromPlace;
					BackgroundAction.TargetPlace = ToPlace;
					BackgroundActions.Add(BackgroundAction);
				}
				BackgroundPlayer.Num = 10;
				BackgroundPlayer.Actions = BackgroundActions;
				BackgroundPlayer.ActionsBackup = BackgroundActions;
				BackgroundPlayer.SectionIndexBias = FMath::RandRange(0, 2333);
				Agents->InitializeAgentState(BackgroundPlayer,"Background");
				Agents->Agents.Add(JsonNode->GetStringField("id")+"_Background", BackgroundPlayer);
			}
		}
	}
	IsReady = true;
}

void AMapMananger::WriteResult()
{
	TSharedPtr<FJsonObject> RootObj = MakeShareable(new FJsonObject());


	RootObj->SetStringField("ver.", "3.0");
	RootObj->SetStringField("annotation", "");

	TArray<TSharedPtr<FJsonValue>> StatisticsValue;
	for (auto Statistic : Agents->Statistics)
	{
		TSharedPtr<FJsonObject> Obj = MakeShareable(new FJsonObject());
		TSharedPtr<FJsonValueObject> ObjValue = MakeShareable(new FJsonValueObject(Obj));

		TSharedPtr<FJsonObject> ObjInner = MakeShareable(new FJsonObject());
		TSharedPtr<FJsonValueObject> ObjInnerValue = MakeShareable(new FJsonValueObject(ObjInner));
		ObjInner->SetNumberField("healthy_num", Statistic.Value.HealthyNum);
		ObjInner->SetNumberField("incubation_num", Statistic.Value.IncubationNum);
		ObjInner->SetNumberField("onset1_num", Statistic.Value.Onset1Num);
		ObjInner->SetNumberField("onset2_num", Statistic.Value.Onset2Num);
		ObjInner->SetNumberField("incubation_num_0", Statistic.Value.IncubationNum0);
		ObjInner->SetNumberField("onset3_num", Statistic.Value.Onset3Num);
		ObjInner->SetNumberField("dead_num", Statistic.Value.DeadNum);
		ObjInner->SetNumberField("recovered_num", Statistic.Value.RecoveredNum);
		ObjInner->SetNumberField("total_num", Statistic.Value.HealthyNum+Statistic.Value.IncubationNum+Statistic.Value.Onset1Num+Statistic.Value.Onset2Num+Statistic.Value.Onset3Num+Statistic.Value.DeadNum+Statistic.Value.RecoveredNum);
		ObjInner->SetNumberField("game_num", Statistic.Value.GameNum);
		ObjInner->SetNumberField("total_action", Statistic.Value.TotalAction);
		ObjInner->SetStringField("game_info", Statistic.Value.GameInfo);
		
		Obj->SetObjectField(Statistic.Key, ObjInner);
		StatisticsValue.Add(ObjValue);
	}

	TArray<TSharedPtr<FJsonValue>> PaintPointsValue;
	int32 Indextp = 0;
	for (auto GridsAndNumbers : Agents->InfectionNumberMapToGridVectorForPaintingPoints)
	{
		TSharedPtr<FJsonObject> Obj = MakeShareable(new FJsonObject());
		TSharedPtr<FJsonValueObject> ObjValue = MakeShareable(new FJsonValueObject(Obj));

		TSharedPtr<FJsonObject> ObjInner = MakeShareable(new FJsonObject());
		TSharedPtr<FJsonValueObject> ObjInnerValue = MakeShareable(new FJsonValueObject(ObjInner));
		ObjInner->SetNumberField("gridx", GridsAndNumbers.Key.X);
		ObjInner->SetNumberField("gridy", GridsAndNumbers.Key.Y);
		ObjInner->SetNumberField("number", GridsAndNumbers.Value);
		
		Obj->SetObjectField(FString::FromInt(Indextp), ObjInner);
		StatisticsValue.Add(ObjValue);
		Indextp += 1;
	}

	TArray<TSharedPtr<FJsonValue>> AgentsValue;
	for (auto Agent : Agents->Agents)
	{
		if (Agent.Value.Type != "Background")
		{
			TSharedPtr<FJsonObject> Obj = MakeShareable(new FJsonObject());
			TSharedPtr<FJsonValueObject> ObjValue = MakeShareable(new FJsonValueObject(Obj));

			TSharedPtr<FJsonObject> ObjInner = MakeShareable(new FJsonObject());
			TSharedPtr<FJsonValueObject> ObjInnerValue = MakeShareable(new FJsonValueObject(ObjInner));

			ObjInner->SetStringField("country", Agent.Value.Country);
			ObjInner->SetStringField("game", Agent.Value.Game);
			ObjInner->SetStringField("state_of_health", Agent.Value.StateOfHealth);
			ObjInner->SetNumberField("num", Agent.Value.Num);

			Obj->SetObjectField(Agent.Key, ObjInner);
			AgentsValue.Add(ObjValue);
		}
	}
	
	RootObj->SetArrayField("statistics", StatisticsValue);
	RootObj->SetArrayField("agents", AgentsValue);

	FString FilePath = FPaths::ProjectDir() + ResultFilePathStr;
	FString JsonStr;
	TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<TCHAR>::Create(&JsonStr);
	FJsonSerializer::Serialize(RootObj.ToSharedRef(), JsonWriter);
	FFileHelper::SaveStringToFile(JsonStr, *FilePath);
}

void AMapMananger::WriteTempResult(FString FileName)
{
	TSharedPtr<FJsonObject> RootObj = MakeShareable(new FJsonObject());


	RootObj->SetStringField("ver.", "3.0");
	RootObj->SetStringField("annotation", "");

	TArray<TSharedPtr<FJsonValue>> StatisticsValue;
	for (auto Statistic : Agents->Statistics)
	{
		TSharedPtr<FJsonObject> Obj = MakeShareable(new FJsonObject());
		TSharedPtr<FJsonValueObject> ObjValue = MakeShareable(new FJsonValueObject(Obj));

		TSharedPtr<FJsonObject> ObjInner = MakeShareable(new FJsonObject());
		TSharedPtr<FJsonValueObject> ObjInnerValue = MakeShareable(new FJsonValueObject(ObjInner));
		ObjInner->SetNumberField("healthy_num", Statistic.Value.HealthyNum);
		ObjInner->SetNumberField("incubation_num", Statistic.Value.IncubationNum);
		ObjInner->SetNumberField("onset1_num", Statistic.Value.Onset1Num);
		ObjInner->SetNumberField("onset2_num", Statistic.Value.Onset2Num);
		ObjInner->SetNumberField("onset3_num", Statistic.Value.Onset3Num);
		ObjInner->SetNumberField("dead_num", Statistic.Value.DeadNum);
		ObjInner->SetNumberField("recovered_num", Statistic.Value.RecoveredNum);
		ObjInner->SetNumberField("total_num", Statistic.Value.HealthyNum+Statistic.Value.IncubationNum+Statistic.Value.Onset1Num+Statistic.Value.Onset2Num+Statistic.Value.Onset3Num+Statistic.Value.DeadNum+Statistic.Value.RecoveredNum);
		ObjInner->SetNumberField("game_num", Statistic.Value.GameNum);
		ObjInner->SetNumberField("total_action", Statistic.Value.TotalAction);
		ObjInner->SetStringField("game_info", Statistic.Value.GameInfo);
		
		Obj->SetObjectField(Statistic.Key, ObjInner);
		StatisticsValue.Add(ObjValue);
	}

	TArray<TSharedPtr<FJsonValue>> PaintPointsValue;
	int32 Indextp = 0;
	for (auto GridsAndNumbers : Agents->InfectionNumberMapToGridVectorForPaintingPoints)
	{
		TSharedPtr<FJsonObject> Obj = MakeShareable(new FJsonObject());
		TSharedPtr<FJsonValueObject> ObjValue = MakeShareable(new FJsonValueObject(Obj));

		TSharedPtr<FJsonObject> ObjInner = MakeShareable(new FJsonObject());
		TSharedPtr<FJsonValueObject> ObjInnerValue = MakeShareable(new FJsonValueObject(ObjInner));
		ObjInner->SetNumberField("gridx", GridsAndNumbers.Key.X);
		ObjInner->SetNumberField("gridy", GridsAndNumbers.Key.Y);
		ObjInner->SetNumberField("number", GridsAndNumbers.Value);
		
		Obj->SetObjectField(FString::FromInt(Indextp), ObjInner);
		StatisticsValue.Add(ObjValue);
		Indextp += 1;
	}

	TArray<TSharedPtr<FJsonValue>> AgentsValue;
	for (auto Agent : Agents->Agents)
	{
		if (Agent.Value.Type != "Background")
		{
			TSharedPtr<FJsonObject> Obj = MakeShareable(new FJsonObject());
			TSharedPtr<FJsonValueObject> ObjValue = MakeShareable(new FJsonValueObject(Obj));

			TSharedPtr<FJsonObject> ObjInner = MakeShareable(new FJsonObject());
			TSharedPtr<FJsonValueObject> ObjInnerValue = MakeShareable(new FJsonValueObject(ObjInner));

			ObjInner->SetStringField("country", Agent.Value.Country);
			ObjInner->SetStringField("game", Agent.Value.Game);
			ObjInner->SetStringField("state_of_health", Agent.Value.StateOfHealth);
			ObjInner->SetNumberField("num", Agent.Value.Num);

			Obj->SetObjectField(Agent.Key, ObjInner);
			AgentsValue.Add(ObjValue);
		}
	}
	
	RootObj->SetArrayField("statistics", StatisticsValue);
	RootObj->SetArrayField("agents", AgentsValue);

	FString FilePath = FPaths::ProjectDir() + FileName;
	FString JsonStr;
	TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<TCHAR>::Create(&JsonStr);
	FJsonSerializer::Serialize(RootObj.ToSharedRef(), JsonWriter);
	FFileHelper::SaveStringToFile(JsonStr, *FilePath);
}


// Called every frame
void AMapMananger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (IsReady)
	{
	
		if (Agents->SimSeconds > 3600*407)
		{
			IsReady = false;
			WriteResult();
		}
		
		float ToolPawnMovementHeight = ToolPawnMovement->GetActorLocation()[2];
		
		Agents->AgentScaleNormal = FVector(FMath::Sqrt(ToolPawnMovementHeight)/4.66f);
		Agents->AgentScaleBackground = Agents->AgentScaleNormal/6.66f;
	
		if (Agents->SimSeconds <= Agents->UpdateAgentsTransformSeconds && Agents->SimSeconds <= Agents->UpdateAgentsHealthSeconds)
		{
			Agents->Statistics.Add(FString::FromInt(Agents->SimSeconds), Agents->Statistic);
			
			Agents->SimSeconds += Agents->SecondsPerTick;


			TArray<FString> GameArr;
			Info[Agents->SimSeconds/3600].ParseIntoArray(GameArr, TEXT(","), false);
			int GameNum = GameArr.Num();
			if (GameArr[0] == "No competitions!")
			{
				GameNum = 0;
			}
			Agents->GameInfo = Info[Agents->SimSeconds/3600];
			Agents->GameNum = GameNum;
			
			GEngine->AddOnScreenDebugMessage(-1, 2.33f, FColor::Red, FString::FromInt(Agents->UpdateAgentsTransformSeconds/3600)+"h"+FString::FromInt(Agents->UpdateAgentsTransformSeconds%3600/60)+"m"+" Total: "+FString::FromInt(Agents->Statistic.TotalNum)+" R: "+FString::SanitizeFloat(Agents->Statistic.R));
			GEngine->AddOnScreenDebugMessage(-1, 2.33f, FColor::Green, FString::FromInt(Agents->UpdateAgentsHealthSeconds/3600)+"h"+FString::FromInt(Agents->UpdateAgentsHealthSeconds%3600/60)+"m"+" "+Agents->Statistic.Info);
			GEngine->AddOnScreenDebugMessage(-1, 2.33f, FColor::Yellow, FString::FromInt(Agents->SimSeconds/3600)+"h"+FString::FromInt(Agents->SimSeconds%3600/60)+"m"+" "+Info[Agents->SimSeconds/3600]);
			// if (Agents->SimSeconds % (6*Agents->SecondsPerTick) == 0)
			// {
				Agents->Act();
			// }
			GEngine->AddOnScreenDebugMessage(-1, 2.33f, FColor::Red, Agents->Logging);
		}
		
		if (TickCount%4 == 0)
		{
			Agents->UpdateAgentsInstanceTransform("Player");
		}
		if (TickCount%4 == 1)
		{
			Agents->UpdateAgentsInstanceTransform("Audience");
		}
		if (TickCount%4 == 2)
		{
			Agents->UpdateAgentsInstanceTransform("Staff");
		}
		if (TickCount%4 == 3)
		{
			Agents->UpdateAgentsInstanceTransform("Background");
		}


		//
		// if (Agents->SimSeconds%(3600*24) == 0)
		// {
		// 	WriteTempResult("Data/History_"+FString::FromInt(Agents->SimSeconds/3600/24)+".json");
		// }

		
		TickCount++;
	}
}



