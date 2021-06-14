// Fill out your copyright notice in the Description page of Project Settings.

#include "TunnelGenerator.h"
#include "TunnelUnit.h"
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

	GetWorld()->GetTimerManager().SetTimer(CreateUnitTimerHandle, this, &ATunnelGenerator::CreateUnit, 1.0f, true, 0);
}

void ATunnelGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATunnelGenerator::CreateUnit()
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
}
