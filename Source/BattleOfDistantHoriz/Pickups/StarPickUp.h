// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickUpBase.h"
#include "StarPickUp.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEOFDISTANTHORIZ_API AStarPickUp : public APickUpBase
{
	GENERATED_BODY()

public:

	AStarPickUp(const FObjectInitializer &ObjectInitializer);
	
	UPROPERTY(Category = ParticleSystem, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UParticleSystemComponent *PlasmaParticle;

	UPROPERTY(Category = ParticleSystem, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UParticleSystemComponent *PlasmaExplodeParticle;


protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void PickUpMeshBeginOverlap(class UPrimitiveComponent *OverlappedComp, class AActor *Other, class UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);



};
