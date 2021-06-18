// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TurretEnemyAI.generated.h"

UCLASS()
class BATTLEOFDISTANTHORIZ_API ATurretEnemyAI : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATurretEnemyAI();
	
	// UPROPERTY(Category = AI, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	// class UAIPerceptionComponent* AIPerception;

	UPROPERTY(Category = AI, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UPawnSensingComponent* AISensing;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnSeePawnByAi(APawn* Pawn);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
