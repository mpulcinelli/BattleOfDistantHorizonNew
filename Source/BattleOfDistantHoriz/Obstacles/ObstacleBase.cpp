// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleOfDistantHoriz/Obstacles/ObstacleBase.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"


// Sets default values
AObstacleBase::AObstacleBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ObstacleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickUpMesh"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_PICK_UP(TEXT("/Game/Geometry/Meshes/PickUpMesh"));

	RootComponent = ObstacleMesh;

	if(SM_PICK_UP.Object!=nullptr){
		ObstacleMesh->SetStaticMesh(SM_PICK_UP.Object);
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

