// Fill out your copyright notice in the Description page of Project Settings.

#include "TunnelGenerator.h"
#include "TunnelUnit.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ArrowComponent.h"

// Sets default values
ATunnelGenerator::ATunnelGenerator()
{
	PrimaryActorTick.bCanEverTick = true;
	USceneComponent *RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	RootComponent = RootComp;
	LocationToSpawn = FVector(0, 0, 0);
}

void ATunnelGenerator::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(CreateUnitTimerHandle, this, &ATunnelGenerator::CreateUnit, 20.0f, true, 0);
}

void ATunnelGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATunnelGenerator::CreateUnit()
{
	if (!CanGenerateNewUnit())
		return;

	for (short int i = 0; i < 2; i++)
	{
		NewUnit();
	}
}

void ATunnelGenerator::NewUnit()
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	if (!LastTunnelCreated)
	{
		LastTunnelCreated = GetWorld()->SpawnActor<ATunnelUnit>(LocationToSpawn, RotationToSpawn, SpawnInfo);
		UE_LOG(LogTemp, Warning, TEXT("[PRIMEIRA VEZ] POSICAO PARA O PRIMEIRO BLOCO %f"), LocationToSpawn.X);
	}
	else
	{
		auto ArrowPosition = LastTunnelCreated->GetArrowPositionNextBlock();
		LocationToSpawn.X += ArrowPosition->GetComponentLocation().X;
		UE_LOG(LogTemp, Warning, TEXT("POSICAO PARA O PROXIMO BLOCO %f"), LocationToSpawn.X);
		LastTunnelCreated = GetWorld()->SpawnActor<ATunnelUnit>(LocationToSpawn, RotationToSpawn, SpawnInfo);
	}

	GeneratedTunnelList.Add(LastTunnelCreated);
}

bool ATunnelGenerator::CanGenerateNewUnit()
{
	TArray<AActor *> TunnelGeneratorList;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATunnelUnit::StaticClass(), TunnelGeneratorList);
	return TunnelGeneratorList.Num() <= 20;
}