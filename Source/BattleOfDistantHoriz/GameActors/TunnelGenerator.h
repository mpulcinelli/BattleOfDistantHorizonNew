// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TunnelGenerator.generated.h"

UCLASS()
class BATTLEOFDISTANTHORIZ_API ATunnelGenerator : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATunnelGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void CreateUnit();

private:
	FTimerHandle CreateUnitTimerHandle;
	FVector LocationToSpawn;
	FRotator RotationToSpawn;
	class ATunnelUnit* LastTunnelCreated = nullptr;
	
};
