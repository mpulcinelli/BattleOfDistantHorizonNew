// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleOfDistantHoriz/Obstacles/ObstableBase.h"


// Sets default values
AObstableBase::AObstableBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AObstableBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AObstableBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

