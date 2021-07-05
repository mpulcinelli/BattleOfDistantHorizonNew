// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleOfDistantHoriz/Obstacles/ObstacleBase.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"


// Sets default values
AObstacleBase::AObstacleBase()
{
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> SM_PICK_UP;
		FConstructorStatics() : SM_PICK_UP(TEXT("/Game/Geometry/Meshes/PickUpMesh")) {}
	};

	static FConstructorStatics ConstructorStatics;

	PrimaryActorTick.bCanEverTick = true;
	ObstacleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickUpMesh"));


	RootComponent = ObstacleMesh;

	if(ConstructorStatics.SM_PICK_UP.Get()!=nullptr){
		ObstacleMesh->SetStaticMesh(ConstructorStatics.SM_PICK_UP.Get());
	}

}

// Called when the game starts or when spawned
void AObstacleBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AObstacleBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

