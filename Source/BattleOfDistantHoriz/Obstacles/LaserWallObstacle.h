// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BattleOfDistantHoriz/Obstacles/ObstableBase.h"
#include "LaserWallObstacle.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEOFDISTANTHORIZ_API ALaserWallObstacle : public AObstableBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALaserWallObstacle();

	UPROPERTY(Category = ParticleSystem, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UParticleSystemComponent *Laser_01_Particle;

	UPROPERTY(Category = ParticleSystem, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UParticleSystemComponent *Laser_02_Particle;

	UPROPERTY(Category = ParticleSystem, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UParticleSystemComponent *Laser_03_Particle;

	UPROPERTY(Category = ParticleSystem, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UParticleSystemComponent *Laser_04_Particle;

	UPROPERTY(Category = ParticleSystem, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UParticleSystemComponent *Laser_05_Particle;

	UPROPERTY(Category = ParticleSystem, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UParticleSystemComponent *Laser_06_Particle;

	UPROPERTY(Category = ParticleSystem, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UParticleSystemComponent *Laser_07_Particle;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
