// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BattleOfDistantHoriz/Pickups/PickUpBase.h"
#include "FuelPickUp.generated.h"

/**
 *
 */
UCLASS()
class BATTLEOFDISTANTHORIZ_API AFuelPickUp : public APickUpBase
{
	GENERATED_BODY()

public:
	AFuelPickUp(const FObjectInitializer &ObjectInitializer);

	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class URectLightComponent *TopLigh;

	UPROPERTY(Category = ParticleSystem, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UParticleSystemComponent *BoltParticle;

	UPROPERTY(Category = ParticleSystem, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UParticleSystemComponent *FuelConsumedParticle;

	UPROPERTY(Category = Audio, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UAudioComponent *AudioComponent;



	UPROPERTY(Category = Rotation, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class URotatingMovementComponent *FuelTankRotation;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void PickUpMeshBeginOverlap(class UPrimitiveComponent *OverlappedComp, class AActor *Other, class UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION()
	void BoltParticleFinished(class UParticleSystemComponent *PSystem);

	float QuantidadeCarga;
	bool bUsedCharge = false;

	FTimerHandle TriggerBoltTimerHandle;
	UFUNCTION()
	void TriggerBoltParticle();

	FORCEINLINE float TimeToRepeatBolt(float Carga) const
	{
		float particleRepeat;
		if (Carga < 30.0)
			particleRepeat = 5.0;
		if (Carga >= 30.0 && Carga < 40.0)
			particleRepeat = 4.5;
		if (Carga >= 40.0 && Carga < 60.0)
			particleRepeat = 3.0;
		if (Carga >= 60.0 && Carga < 80.0)
			particleRepeat = 2.0;
		if (Carga >= 80.0)
			particleRepeat = 1.0;
		return particleRepeat;
	}
};
