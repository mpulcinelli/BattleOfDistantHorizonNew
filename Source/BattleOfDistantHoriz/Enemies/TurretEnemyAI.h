// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIModule/Classes/AIController.h"
#include "TurretEnemyAI.generated.h"

UCLASS()
class BATTLEOFDISTANTHORIZ_API ATurretEnemyAI : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATurretEnemyAI();

private:

void FireSelection(FVector Loc, FRotator Rot);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnSeePawnByAi(class APawn* SeenPawn);


	UPROPERTY(VisibleAnywhere, Category="IA")
	class UPawnSensingComponent * PawnSensing;

public:

	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
