// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "TunnelUnit.generated.h"

UCLASS()
class BATTLEOFDISTANTHORIZ_API ATunnelUnit : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATunnelUnit();

	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent *TunnelUnitMesh;
	
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent *EndTrigger;
	
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent *AreaToSpawn;

	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent *AreaToSpawnFuelPickUp;

	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UPointLightComponent *PoitLight01;
	
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UPointLightComponent *PoitLight02;
	
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UPointLightComponent *PoitLight03;
	
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UPointLightComponent *PoitLight04;			
	
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UPointLightComponent *PoitLight05;

	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UArrowComponent *ArrowPositionNextBlock;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
	
	void AddPickUpFuel();
	void AddPickUpStar();
	void AddLaserWall();

	void GetRandomPointIn3DBoxSpace(FVector &RandomPoint, class UBoxComponent* BoundingBox);
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE class UArrowComponent* GetArrowPositionNextBlock() const { return ArrowPositionNextBlock; }

private:
	UFUNCTION()
	void EndTriggerBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* Other, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	TArray<AActor*> ListOfCreatedActors;
	void ShuffleLight(int OptShuffle);
	bool bIsPendingKill=false;

	FORCEINLINE FLinearColor GetRandColor() const { 
		switch(FMath::RandRange(0, 2)){
			case 0:
				return FLinearColor::Red;
			case 1:
				return FLinearColor::Green;
			case 2:
				return FLinearColor::Blue;
			default:
				return FLinearColor::White;
		}
	}
};
