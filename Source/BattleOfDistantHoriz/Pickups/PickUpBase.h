// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUpBase.generated.h"

UCLASS()
class BATTLEOFDISTANTHORIZ_API APickUpBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickUpBase(const FObjectInitializer& ObjectInitializer);
	
	class UStaticMeshComponent *PickUpMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	
	
};
