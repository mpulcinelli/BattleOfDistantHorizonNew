// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObstableBase.generated.h"

UCLASS()
class BATTLEOFDISTANTHORIZ_API AObstableBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AObstableBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class UStaticMeshComponent *PickUpMesh;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;



};
