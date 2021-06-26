// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleOfDistantHoriz/Obstacles/ObstableBase.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"


// Sets default values
AObstableBase::AObstableBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PickUpMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickUpMesh"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_PICK_UP(TEXT("/Game/Geometry/Meshes/PickUpMesh"));

	RootComponent = PickUpMesh;

	if(SM_PICK_UP.Object!=nullptr){
		PickUpMesh->SetStaticMesh(SM_PICK_UP.Object);
	}

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

