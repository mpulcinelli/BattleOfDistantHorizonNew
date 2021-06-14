// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpaceShipProjectile.generated.h"

UCLASS()
class BATTLEOFDISTANTHORIZ_API ASpaceShipProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpaceShipProjectile();
	class UParticleSystemComponent *ProjectileParticle;
	class USphereComponent *SphereCollider;
	class UProjectileMovementComponent *ProjectileMovimentComp;

private:
	class UParticleSystem *Projectile01_Hit_Particle;
	class UParticleSystem *Projectile01_Particle;
	TArray<class UParticleSystem *> Particles;
	int SelectedPosition = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UFUNCTION()
	void SphereColliderBeginOverlap(class UPrimitiveComponent *OverlappedComp, class AActor *Other, class UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	void ExecuteFire(int Pos);
};
