// Fill out your copyright notice in the Description page of Project Settings.


#include "Agents.h"


// Sets default values
AAgents::AAgents()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Observation.Add(0);
	Observation.Add(0);
	Observation.Add(0);
	Observation.Add(0);
	
	SIOClientComponent = CreateDefaultSubobject<USocketIOClientComponent>(TEXT("SocketIOClientComponent"));
	SIOClientComponent->AddressAndPort = TEXT("http://localhost:2333");
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Vehicle01(TEXT("StaticMesh'/Game/Meshes/Vehicles/SK_Veh_Car_Sports_01.SK_Veh_Car_Sports_01'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Vehicle02(TEXT("StaticMesh'/Game/Meshes/Vehicles/SK_Veh_Car_Taxi_01.SK_Veh_Car_Taxi_01'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Vehicle03(TEXT("StaticMesh'/Game/Meshes/Vehicles/SK_Veh_Car_Van_01.SK_Veh_Car_Van_01'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Person01(TEXT("StaticMesh'/Game/Meshes/Characters/SM_Pawn_Walk_Male_01.SM_Pawn_Walk_Male_01'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Player(TEXT("StaticMesh'/Game/Meshes/Characters/PlayerStaticMesh.PlayerStaticMesh'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Audience(TEXT("StaticMesh'/Game/Meshes/Characters/AudienceStaticMesh.AudienceStaticMesh'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Staff(TEXT("StaticMesh'/Game/Meshes/Characters/StaffStaticMesh.StaffStaticMesh'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Background(TEXT("StaticMesh'/Game/Meshes/Vehicles/SK_Veh_Car_Sports_01.SK_Veh_Car_Sports_01'"));
	
	HISMC.Add("Vehicle01", CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("Vehicle01")));
	HISMC.FindRef("Vehicle01")->SetupAttachment(RootComponent);
	HISMC.FindRef("Vehicle01")->SetStaticMesh(Vehicle01.Object);

	HISMC.Add("Vehicle02", CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("Vehicle02")));
	HISMC.FindRef("Vehicle02")->SetupAttachment(RootComponent);
	HISMC.FindRef("Vehicle02")->SetStaticMesh(Vehicle02.Object);

	HISMC.Add("Vehicle03", CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("Vehicle03")));
	HISMC.FindRef("Vehicle03")->SetupAttachment(RootComponent);
	HISMC.FindRef("Vehicle03")->SetStaticMesh(Vehicle03.Object);

	HISMC.Add("Person01", CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("Person01")));
	HISMC.FindRef("Person01")->SetupAttachment(RootComponent);
	HISMC.FindRef("Person01")->SetStaticMesh(Person01.Object);

	HISMC.Add("Player", CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("Player")));
	HISMC.FindRef("Player")->SetupAttachment(RootComponent);
	HISMC.FindRef("Player")->SetStaticMesh(Player.Object);

	HISMC.Add("Audience", CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("Audience")));
	HISMC.FindRef("Audience")->SetupAttachment(RootComponent);
	HISMC.FindRef("Audience")->SetStaticMesh(Audience.Object);

	HISMC.Add("Staff", CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("Staff")));
	HISMC.FindRef("Staff")->SetupAttachment(RootComponent);
	HISMC.FindRef("Staff")->SetStaticMesh(Staff.Object);

	HISMC.Add("Background", CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("Background")));
	HISMC.FindRef("Background")->SetupAttachment(RootComponent);
	HISMC.FindRef("Background")->SetStaticMesh(Background.Object);
}



void AAgents::Reset()
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
	TArray<TSharedPtr<FJsonValue>> Array;
	// Array.Add(MakeShareable(new FJsonValueNumber(0)));
	Array.Add(MakeShareable(new FJsonValueNumber(0)));
	// Array.Add(MakeShareable(new FJsonValueNumber(0)));
	// Array.Add(MakeShareable(new FJsonValueNumber(0)));
	JsonObject->SetArrayField(TEXT("observation"), Array);
	SIOClientComponent->EmitNative(TEXT("reset"), JsonObject);
}

void AAgents::Act()
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
	TArray<TSharedPtr<FJsonValue>> Array;
	float Reward = (-1*Statistic.Onset1Num-1*Statistic.Onset2Num-1*Statistic.DeadNum+1*Statistic.RecoveredNum)*0.25f;
	
	if (ActionReceived == 0)
	{
		TotalAction = 0;
		Reward += 0*GameNum;
	} else
	{
		TotalAction = 1;
		Reward -= 0*GameNum;
	}
	// UE_LOG(LogTemp, Warning, TEXT("%i"), Observation.Num());
	// Array.Add(MakeShareable(new FJsonValueNumber(Observation[0])));
	Array.Add(MakeShareable(new FJsonValueNumber(Observation[1])));
	// Array.Add(MakeShareable(new FJsonValueNumber(GameNum)));
	// Array.Add(MakeShareable(new FJsonValueNumber(Observation[3])));
	JsonObject->SetArrayField(TEXT("observation"), Array);
	JsonObject->SetNumberField(TEXT("reward"), Reward);

	bool Done;

	TArray<TSharedPtr<FJsonValue>> Info;
	Info.Add(MakeShareable(new FJsonValueNumber(Statistic.R)));
	Info.Add(MakeShareable(new FJsonValueNumber(Statistic.HealthyNum)));
	Info.Add(MakeShareable(new FJsonValueNumber(Statistic.Onset1Num)));
	Info.Add(MakeShareable(new FJsonValueNumber(Statistic.Onset2Num)));
	Info.Add(MakeShareable(new FJsonValueNumber(Statistic.Onset3Num)));
	Info.Add(MakeShareable(new FJsonValueNumber(Statistic.DeadNum)));
	Info.Add(MakeShareable(new FJsonValueNumber(Statistic.RecoveredNum)));
	JsonObject->SetArrayField(TEXT("info"), Info);
	if (SimSeconds > 3600*407)
	{
		Done = true;
		if (IsDone == false)
		{
			JsonObject->SetBoolField(TEXT("done"), Done);
			SIOClientComponent->EmitNative(TEXT("step"), JsonObject);
		}
		IsDone = true;
	} else
	{
		Done = false;
		JsonObject->SetBoolField(TEXT("done"), Done);
		SIOClientComponent->EmitNative(TEXT("step"), JsonObject);
	}
}


void AAgents::InitGrids()
{
	int TotalNum = 14000000;
	float XWidth = (UpperRight.X-BottomLeft.X)/GridSize;
	float YWidth = (UpperRight.Y-BottomLeft.Y)/GridSize;
	for (int i = 0; i < 1*GridSize*GridSize; i ++)
	{
		FGrid Grid;
		int XIndex = i/GridSize;
		int YIndex = i%GridSize;
		float XLeft = BottomLeft.X+XIndex*XWidth;
		float XRight = BottomLeft.X+(XIndex+1)*XWidth;
		float YBottom = BottomLeft.Y+YIndex*YWidth;
		float YUpper = BottomLeft.Y+(YIndex+1)*YWidth;
		Grid.XIndex = XIndex;
		Grid.YIndex = YIndex;
		Grid.GridBottomLeft = FVector(XLeft, YBottom, 0);
		Grid.GridUpperRight = FVector(XRight, YUpper, 0);
		Grid.GridCenter = (Grid.GridBottomLeft+Grid.GridUpperRight)/2;
		Grids.Add(Grid);
		InfectionNumberMapToGridVectorForPaintingPoints.Add(FVector(XIndex, YIndex, 0), 0);
		// DrawDebugLine(GetWorld(), FVector(XLeft, BottomLeft.Y, 0), FVector(XLeft, UpperRight.Y, 0), FColor::Magenta, true);
		// DrawDebugLine(GetWorld(), FVector(BottomLeft.X, YBottom, 0), FVector(BottomLeft.Y, YBottom, 0), FColor::Magenta, true);
	}
	for (int i = GridSize*GridSize; i <= 2*GridSize*GridSize; i ++)
	{
		FGrid Grid;
		int XIndex = (i-GridSize*GridSize)/GridSize;
		int YIndex = i%GridSize;
		float XLeft = BottomLeft.X+XIndex*XWidth;
		float XRight = BottomLeft.X+(XIndex+1)*XWidth;
		float YBottom = BottomLeft.Y+YIndex*YWidth;
		float YUpper = BottomLeft.Y+(YIndex+1)*YWidth;
		Grid.XIndex = XIndex;
		Grid.YIndex = YIndex;
		Grid.GridBottomLeft = FVector(XLeft, YBottom, 2333);
		Grid.GridUpperRight = FVector(XRight, YUpper, 2333);
		Grid.GridCenter = (Grid.GridBottomLeft+Grid.GridUpperRight)/2;
		Grids.Add(Grid);
		// DrawDebugLine(GetWorld(), FVector(XLeft, BottomLeft.Y, 2333), FVector(XLeft, UpperRight.Y, 2333), FColor::Magenta, true);
		// DrawDebugLine(GetWorld(), FVector(BottomLeft.X, YBottom, 2333), FVector(BottomLeft.Y, YBottom, 2333), FColor::Magenta, true);
	}
	for (auto Building : Buildings)
	{
		int XIndex = FMath::FloorToInt((Building.X-BottomLeft.X)/(UpperRight.X-BottomLeft.X)*GridSize);
		int YIndex = FMath::FloorToInt((Building.Y-BottomLeft.Y)/(UpperRight.Y-BottomLeft.Y)*GridSize);
		for (int X = XIndex-3; X <= XIndex+3; X++)
		{
			for (int Y = YIndex-3; Y <= YIndex+3; Y++)
			{
				if (0 <= X && X < GridSize && 0 <= Y && Y < GridSize)
				{
					Grids[X*GridSize+Y].HealthyNum += 10;
					TotalNum -= 10;
				}
			}
		}
	}
	for (int N = TotalNum; N > 0; N--)
	{
		Grids[FMath::RandRange(0, GridSize*GridSize-1)].HealthyNum += 1;
	}
}

void AAgents::InitializeAgentState(FAgent& Agent, FString Type)
{
	auto Action = Agent.Actions[Agent.ActionIndex];
	Agent.Location = Places.FindRef(Action.CurrentPlace).Location;
	Agent.Type = Type;
	if (Agent.Type == "Background")
	{
		Agent.Route = Routes2.FindRef(Action.CurrentPlace+"_"+Action.TargetPlace);
		TArray<FSection> RouteTemp;
		for (int i = 0; i < Agent.Route.Num(); i++)
		{
			int IndexTemp = (i+Agent.SectionIndexBias)%Agent.Route.Num();
			RouteTemp.Add(Agent.Route[IndexTemp]);
		}
		Agent.Route = RouteTemp;
		Agent.SectionIndex = 0;
		Agent.SectionRate = 0;
	}
	Agent.Transform = FTransform(Agent.Rotation, Agent.Location, Agent.Scale);
	HISMC.FindRef(Agent.Type)->AddInstance(Agent.Transform);
	Agent.InstanceIndex = HISMC.FindRef(Agent.Type)->GetInstanceCount()-1;
}

void AAgents::UpdateAgentsHealth()
{
	if (UpdateAgentsHealthSeconds <= SimSeconds)
	{
		for (int i = 0; i < Grids.Num(); i++)
		{
			Grids[i].HealthyNumTemp = Grids[i].HealthyNum;
			Grids[i].IncubationNumTemp = Grids[i].IncubationNum;
			Grids[i].Onset1NumTemp = Grids[i].Onset1Num;
			Grids[i].Onset2NumTemp = Grids[i].Onset2Num;
			Grids[i].Onset3NumTemp = Grids[i].Onset3Num;
			Grids[i].DeadNumTemp = Grids[i].DeadNum;
			Grids[i].RecoveredNumTemp = Grids[i].RecoveredNum;
		}
		for (auto& AgentItr : Agents)
		{
			auto Agent = &AgentItr.Value;
			int Index = Agent->GridIndex;
			int Num = Agent->Num;
			FString State = Agent->StateOfHealth;
			if (Index >= 0 && Index < Grids.Num())
			{
				if (State == "Healthy")
				{
					Grids[Index].HealthyNumTemp += Num;
				}
				if (State == "Incubation")
				{
					Grids[Index].IncubationNumTemp += Num;
				}
				if (State == "Onset1")
				{
					Grids[Index].Onset1NumTemp += Num;
				}
				if (State == "Onset2")
				{
					Grids[Index].Onset2NumTemp += Num;
				}
				if (State == "Onset3")
				{
					Grids[Index].Onset3NumTemp += Num;
				}
				if (State == "Dead")
				{
					Grids[Index].DeadNumTemp += Num;
				}
				if (State == "Recovered")
				{
					Grids[Index].RecoveredNumTemp += Num;
				}
			}
		}

		float GridIncubationDaysEvaluate = 0;
		int GridIncubationDaysEvaluateNum = 0;
		for (int i = 0; i < Grids.Num(); i++)
		{	
			float P = 1-FMath::Pow(1-IncubationInfectionRate, Grids[i].IncubationNumTemp);
			
			Grids[i].NewIncubationNum = FMath::FloorToInt(Grids[i].HealthyNum*P);
			
			Grids[i].HealthyNum -= Grids[i].NewIncubationNum;
			Grids[i].IncubationNum += Grids[i].NewIncubationNum;

			int NewOnset1Num = FMath::FloorToInt(Grids[i].IncubationNum*OnsetInfectionRate);
			Grids[i].IncubationNum -= NewOnset1Num;
			Grids[i].Onset1Num += NewOnset1Num;

			int NewOnset2Num = FMath::FloorToInt(Grids[i].Onset1Num*OnsetInfectionRate);
			Grids[i].Onset1Num -= NewOnset2Num;
			Grids[i].Onset2Num += NewOnset2Num;

			int NewOnset3Num = FMath::FloorToInt(Grids[i].Onset2Num*OnsetInfectionRate);
			Grids[i].Onset2Num -= NewOnset3Num;
			Grids[i].Onset3Num += NewOnset3Num;

			int NewDeadNum = FMath::FloorToInt(Grids[i].Onset3Num*DeathRate);
			int NewRecoveredNum = Grids[i].Onset3Num-NewDeadNum;
			Grids[i].Onset3Num = 0;
			Grids[i].DeadNum += NewDeadNum;
			Grids[i].RecoveredNum += NewRecoveredNum;
	
			Grids[i].P = P;
			if (Grids[i].IncubationNumTemp >= 10)
			{
				GridIncubationDaysEvaluate += 1.f/P;
				GridIncubationDaysEvaluateNum += 1;
			}
		}
		GridIncubationDaysEvaluate /= GridIncubationDaysEvaluateNum;
		
		for (auto& AgentItr : Agents)
		{
			auto Agent = &AgentItr.Value;
			if (Agent->GridIndex >= 0 && Agent->GridIndex < Grids.Num())
			{
				Agent->InfectionNum += Grids[Agent->GridIndex].InfectionNum*Agent->Num;
			}
		}
		for (auto& AgentItr : Agents)
		{
			auto Agent = &AgentItr.Value;
			int Index = Agent->GridIndex;
			FString Action = Agent->Actions[Agent->ActionIndex].Action;
			FString State = Agent->StateOfHealth;
			if (Index >= 0 && Index < Grids.Num())
			{
				auto Grid = Grids[Index];
				FString NewStateOfHealth = State;
				if (State == "Healthy" && Action != "shuijiao")
				{
					if (FMath::RandRange(0.f, 1.f) < Grid.P)
					{
						NewStateOfHealth = "Incubation";
						Grids[Index].NewIncubationNum += Agent->Num;
					}
				}
				if (State == "Incubation")
				{
					if (FMath::RandRange(0.f, 1.f) < OnsetInfectionRate)
					{
						NewStateOfHealth = "Onset1";
						if (Agent->Type != "Background")
						{
							Agent->ChangingMethod = "GoToHospital";
						}
					}
				}
				if (State == "Onset1")
				{
					if (FMath::RandRange(0.f, 1.f) < OnsetInfectionRate)
					{
						NewStateOfHealth = "Onset2";
					}
				}
				if (State == "Onset2")
				{
					if (FMath::RandRange(0.f, 1.f) < OnsetInfectionRate)
					{
						NewStateOfHealth = "Onset3";
					}
				}
				if (State == "Onset3")
				{
					if (FMath::RandRange(0.f, 1.f) < DeathRate)
					{
						NewStateOfHealth = "Dead";
					} else
					{
						NewStateOfHealth = "Recovered";
					}
				}
				if (State == "Dead")
				{
	
				}
				if (State == "Recovered")
				{
	
				}
				Agent->StateOfHealth = NewStateOfHealth;
			}
		}

		for (int i = 0; i < Grids.Num(); i++)
		{
			if (Grids[i].NewIncubationNum > 0)
			{
				InfectionNumberMapToGridVectorForPaintingPoints[FVector(Grids[i].XIndex, Grids[i].YIndex, 0)] += Grids[i].NewIncubationNum;
			}
		}
		
		for (int i = 0; i < Grids.Num(); i++)
		{	
			if (Grids[i].IncubationNumTemp-Grids[i].IncubationNum != 0)
			{
				Grids[i].InfectionNum = Grids[i].NewIncubationNum*1.f/(Grids[i].IncubationNumTemp-Grids[i].IncubationNum);
			}
			else
			{
				Grids[i].InfectionNum = 0;
			}
		}

		int HealthyNumTemp = 0;
		int IncubationNumTemp = 0;
		int Onset1NumTemp = 0;
		int Onset2NumTemp = 0;
		int Onset3NumTemp = 0;
		int DeadNumTemp = 0;
		int RecoveredNumTemp = 0;
		
		for (int i = 0; i < Grids.Num(); i++)
		{
			HealthyNumTemp += Grids[i].HealthyNum;
			IncubationNumTemp += Grids[i].IncubationNum;
			Onset1NumTemp += Grids[i].Onset1Num;
			Onset2NumTemp += Grids[i].Onset2Num;
			Onset3NumTemp += Grids[i].Onset3Num;
			DeadNumTemp += Grids[i].DeadNum;
			RecoveredNumTemp = Grids[i].RecoveredNum;
		}
		
		float TotalR = 0;
		float IncubationNum0 = 0;
		int TotalCount = 0;
		for (auto& AgentItr : Agents)
		{
			auto Agent = &AgentItr.Value;
			int Num = Agent->Num;

			FString State = Agent->StateOfHealth;

			if (Agent->IsFirstClass)
			{
				if (State == "Incubation")
				{
					IncubationNum0 += 1;
				}
			}
			
			
			if (State == "Healthy")
			{
				HealthyNumTemp += Num;
			}
			if (State == "Incubation")
			{
				IncubationNumTemp += Num;
			}
			if (State == "Onset1")
			{
				TotalR += Agent->InfectionNum;
				TotalCount += Agent->Num;
				Onset1NumTemp += Num;
			}
			if (State == "Onset2")
			{
				TotalR += Agent->InfectionNum;
				TotalCount += Agent->Num;
				Onset2NumTemp += Num;
			}
			if (State == "Onset3")
			{
				TotalR += Agent->InfectionNum;
				TotalCount += Agent->Num;
				Onset3NumTemp += Num;
			}
			if (State == "Dead")
			{
				TotalR += Agent->InfectionNum;
				TotalCount += Agent->Num;
				DeadNumTemp += Num;
			}
			if (State == "Recovered")
			{
				TotalR += Agent->InfectionNum;
				TotalCount += Agent->Num;
				RecoveredNumTemp += Num;
			}
		}
		if (TotalCount > 0)
		{
			Statistic.R = TotalR/TotalCount;
		} else
		{
			Statistic.R = 0;
		}

		Statistic.HealthyNum = HealthyNumTemp;
		Statistic.IncubationNum = IncubationNumTemp;
		Statistic.Onset1Num = Onset1NumTemp;
		Statistic.Onset2Num = Onset2NumTemp;
		Statistic.Onset3Num = Onset3NumTemp;
		Statistic.DeadNum = DeadNumTemp;
		Statistic.RecoveredNum = RecoveredNumTemp;

		Statistic.IncubationNum0 = IncubationNum0;
		Statistic.GridIncubationDay = GridIncubationDaysEvaluate;
		
		Statistic.GameNum = GameNum;
		Statistic.TotalAction = TotalAction;
		Statistic.GameInfo = GameInfo;
		
		Statistic.TotalNum = Statistic.HealthyNum+Statistic.IncubationNum+Statistic.Onset1Num+Statistic.Onset2Num+Statistic.Onset3Num+Statistic.DeadNum+Statistic.RecoveredNum;
		Statistic.Info = "Healthy: "+FString::FromInt(Statistic.HealthyNum)+" Incubation: "+FString::FromInt(Statistic.IncubationNum)+" Onset: "+FString::FromInt(Statistic.Onset1Num+Statistic.Onset2Num+Statistic.Onset3Num)+" Dead: "+FString::FromInt(Statistic.DeadNum)+" Recovered: "+FString::FromInt(Statistic.RecoveredNum);
		Observation[0] = Statistic.HealthyNum;
		Observation[1] = Statistic.Onset1Num+Statistic.Onset2Num+Statistic.Onset3Num;
		Observation[2] = Statistic.DeadNum;
		Observation[3] = Statistic.RecoveredNum;
		UpdateAgentsHealthSeconds += SecondsPerTick;
	} else
	{
		FPlatformProcess::Sleep(0.01f);
	}
	
}

void AAgents::UpdateAgentsActions()
{

	for (auto& AgentItr : Agents)
	{
		auto Agent = &AgentItr.Value;
		if (Agent->Type != "Background")
		{
			if (Agent->ChangingMethod != "")
			{
				ChangeActions(*Agent, Agent->ChangingMethod);
				Agent->ChangingMethod == "";
			} else
			{
				if (Agent->InHospital == false)
				{
					if (TotalAction == 0)
					{
						ChangeActions(*Agent, "Recover");
					}
					if (TotalAction == 1)
					{
						ChangeActions(*Agent, "Stop");
					}
				}
			}
		}	
	}
}

void AAgents::UpdateAgentsTransform()
{
	if (UpdateAgentsTransformSeconds <= SimSeconds)
	{
		int SimHours = UpdateAgentsTransformSeconds/3600;
		float SecondsRate = (UpdateAgentsTransformSeconds-SimHours*3600)/3600.1f;

		if (SimHours != SimHoursRecord)
		{
			for (auto& AgentItr : Agents)
			{
				auto Agent = &AgentItr.Value;
				Agent->ActionIndex = SimHours;			
				
				auto Action = Agent->Actions[Agent->ActionIndex];
				if (Action.Action == "yidong")
				{
					if (Agent->Type != "Background" && Action.CurrentPlace != Action.TargetPlace)
					{
						Agent->Route = Routes.FindRef(Action.CurrentPlace+"_"+Action.TargetPlace);
						Agent->SectionIndex = 0;
						Agent->SectionRate = 0;
					}
				}
				if (Action.Action == "xianguang")
				{
					if (Action.CurrentPlace != Action.TargetPlace)
					{
						Agent->Route = Routes.FindRef(Action.CurrentPlace+"_"+Action.TargetPlace);
						Agent->SectionIndex = 0;
						Agent->SectionRate = 0;
					}
				}
				if (Action.Action == "likai")
				{
					Agent->Location = FVector(9999999, 9999999, 0);
				}
				if (Agent->Type != "Background")
				{
					Agent->Scale = AgentScaleNormal;
				} else
				{
					Agent->Scale = AgentScaleBackground;
				}
				Agent->Transform = FTransform(Agent->Rotation, Agent->Location, Agent->Scale);
				Agent->GridIndex = GetGridIndex(Agent->Location);
			}
			SimHoursRecord = SimHours;
		} else
		{
			for (auto& AgentItr : Agents)
			{
				auto Agent = &AgentItr.Value;
				auto Action = Agent->Actions[Agent->ActionIndex];
				if (Action.Action == "yidong" || Action.Action == "xianguang" && Action.CurrentPlace != Action.TargetPlace)
				{
					if (Agent->Type != "Background")
					{
						Agent->SectionIndex = FMath::FloorToInt(Agent->Route.Num()*(SecondsRate+Agent->SectionRateBias));
						Agent->SectionRate = FMath::Min((SecondsRate+Agent->SectionRateBias)*Agent->Route.Num()-Agent->SectionIndex, 1.f);
						Agent->Scale = AgentScaleNormal;
					} else
					{
						Agent->SectionIndex = FMath::FloorToInt(Agent->Route.Num()*SecondsRate);
						Agent->SectionRate = FMath::Min(SecondsRate*Agent->Route.Num()-Agent->SectionIndex, 1.f);
						Agent->Scale = AgentScaleBackground;
					}
					if (Agent->SectionIndex < Agent->Route.Num())
					{
						FVector Location1 = Agent->Route[Agent->SectionIndex].Location1;
						FVector Location2 = Agent->Route[Agent->SectionIndex].Location2;
						Agent->Location = Location1*(1-Agent->SectionRate)+Location2*Agent->SectionRate;
						Agent->Rotation = (Location2-Location1).Rotation();
						Agent->Transform = FTransform(Agent->Rotation, Agent->Location, Agent->Scale);
						Agent->GridIndex = Agent->Route[Agent->SectionIndex].GridIndex;
					}
				} else
				{
					if (Action.Action == "yidong" || Action.Action == "xianguang" && Action.CurrentPlace == Action.TargetPlace)
					{
						RandomMoveAgent(*Agent, Places.FindRef(Action.CurrentPlace).Location, 0.f, 10000.f*FMath::Sin(SecondsRate*3.1416f));
					}
					if (Action.Action == "jichang" || Action.Action == "shuijiao")
					{
						RandomMoveAgent(*Agent, Places.FindRef(Action.CurrentPlace).Location, 0.f, 20000.f);
					}
					if (Action.Action == "yiyuan")
					{
						if (Agent->StateOfHealth != "Dead")
						{
							RandomMoveAgent(*Agent, Places.FindRef(Action.CurrentPlace).Location, 0.f, 10000.f);
						} else
						{
							Agent->Location = Places.FindRef(Action.CurrentPlace).Location;
							Agent->Location[2] = 100000;
						}
					}
					if (Action.Action == "bisai")
					{
						if (Agent->Type != "Audience")
						{
							RandomMoveAgent(*Agent, Places.FindRef(Action.CurrentPlace).Location, 0.f, 11666.f);
						} else
						{
							RandomMoveAgent(*Agent, Places.FindRef(Action.CurrentPlace).Location, 10000.f, 12333.f);
						}
					}
					Agent->Transform = FTransform(Agent->Rotation, Agent->Location, Agent->Scale);
					Agent->GridIndex = GetGridIndex(Agent->Location);
				}
			}
		}

		UpdateAgentsTransformSeconds += SecondsPerTick;
	} else
	{
		FPlatformProcess::Sleep(0.01f);
	}
}

void AAgents::UpdateAgentsInstanceTransform(FString Type)
{
	for (auto& AgentItr : Agents)
	{
		auto Agent = &AgentItr.Value;
		if (Agent->Type == Type)
		{
			HISMC.FindRef(Agent->Type)->UpdateInstanceTransform(Agent->InstanceIndex, Agent->Transform, true);
		}
	}
}

void AAgents::ChangeActions(FAgent& Agent, FString Method)
{
	if (Method == "GoToHospital" && Agent.ActionIndex+1 < Agent.Actions.Num())
	{
		FString HospitalID;
		for (int i = Agent.ActionIndex+1; i < Agent.Actions.Num(); i++)
		{
			if (i == Agent.ActionIndex+1)
			{
				FAction NewAction;
				NewAction.Action = "yidong";
				NewAction.CurrentPlace = Agent.Actions[Agent.ActionIndex].CurrentPlace;
				HospitalID = HospitalIDList[FMath::RandRange(0, HospitalIDList.Num()-1)];
				NewAction.TargetPlace = HospitalID;
				Agent.Actions[i] = NewAction;
			} else
			{
				FAction NewAction;
				NewAction.Action = "yiyuan";
				NewAction.CurrentPlace = HospitalID;
				NewAction.TargetPlace = HospitalID;
				Agent.Actions[i] = NewAction;
			}
		}
		Agent.InHospital = true;
	}
	if (Method == "Stop" && Agent.ActionIndex+1 < Agent.Actions.Num())
	{
		for (int i = Agent.ActionIndex+1; i < Agent.Actions.Num(); i++)
		{
			FAction NewAction;
			NewAction.Action = "shuijiao";
			NewAction.CurrentPlace = Agent.ActionsBackup[0].CurrentPlace;
			NewAction.TargetPlace = Agent.ActionsBackup[0].CurrentPlace;
			Agent.Actions[i] = NewAction;
		}
		// for (int i = Agent.ActionIndex+1; i < Agent.Actions.Num(); i++)
		// {
		// 	if (Agent.Actions[i].Action == "xianguang" || Agent.Actions[i].Action == "bisai")
		// 	{
		// 		FAction NewAction;
		// 		NewAction.Action = "shuijiao";
		// 		NewAction.CurrentPlace = Agent.ActionsBackup[0].CurrentPlace;
		// 		NewAction.TargetPlace = Agent.ActionsBackup[0].CurrentPlace;
		// 		Agent.Actions[i] = NewAction;
		// 	} else if (Agent.Actions[i].Action == "yidong" && i < Agent.Actions.Num()-1)
		// 	{ 
		// 		if (Agent.Actions[i+1].Action == "xianguang" || Agent.Actions[i+1].Action == "bisai")
		// 		{
		// 			FAction NewAction;
		// 			NewAction.Action = "yidong";
		// 			NewAction.CurrentPlace = Agent.Actions[i].CurrentPlace;
		// 			NewAction.TargetPlace = Agent.ActionsBackup[0].CurrentPlace;
		// 			Agent.Actions[i] = NewAction;
		// 		}
		// 	}
		// }
	}
	if (Method == "Recover" && Agent.ActionIndex+1 < Agent.Actions.Num())
	{
		for (int i = Agent.ActionIndex+1; i < Agent.Actions.Num(); i++)
		{
			Agent.Actions[i] = Agent.ActionsBackup[i];
		}
		// for (int i = Agent.ActionIndex+1; i < Agent.Actions.Num(); i++)
		// {
		// 	if (i == Agent.ActionIndex+1)
		// 	{
		// 		if (Agent.Actions[i].TargetPlace != Agent.ActionsBackup[i].TargetPlace)
		// 		{
		// 			FAction NewAction;
		// 			NewAction.Action = "yidong";
		// 			NewAction.CurrentPlace = Agent.Actions[i].CurrentPlace;
		// 			NewAction.TargetPlace = Agent.ActionsBackup[i].TargetPlace;
		// 			Agent.Actions[i] = NewAction;
		// 		}
		// 	} else
		// 	{
		// 		Agent.Actions[i] = Agent.ActionsBackup[i];
		// 	}
		// }
	}
}

void AAgents::RandomMoveAgent(FAgent& Agent, FVector Center, float Radius1, float Radius2)
{
	float Theta = FMath::RandRange(0.f, 10000.f);
	float Row = FMath::RandRange(Radius1, Radius2);
	Agent.Location[0] = Center[0]+Row*FMath::Cos(Theta);
	Agent.Location[1] = Center[1]+Row*FMath::Sin(Theta);
}


// Called when the game starts or when spawned
void AAgents::BeginPlay()
{
	Super::BeginPlay();

	Reset();

	SIOClientComponent->OnNativeEvent(TEXT("act"), [this](const FString& Event, const TSharedPtr<FJsonValue>& Message)
	{
	    TSharedPtr<FJsonObject> JsonNode = Message->AsObject();
		Logging = *USIOJConvert::ToJsonString(JsonNode->GetObjectField("logging"));
		ActionReceived = JsonNode->GetIntegerField("action");
	    if (ActionReceived == -1)
	    {
	        Reset();
	    } else
	    {
			GEngine->AddOnScreenDebugMessage(-1, 2.33f, FColor::Black, Logging);
	    }
	});
}



// Called every frame
void AAgents::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

