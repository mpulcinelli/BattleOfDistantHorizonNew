// Fill out your copyright notice in the Description page of Project Settings.

#include "StarObstacle.h"
#include "UObject/ConstructorHelpers.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "BattleOfDistantHoriz/Characters/SpaceShipPawn.h"

AStarObstacle::AStarObstacle()
{

	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UParticleSystem> PS_PLASMA;
        ConstructorHelpers::FObjectFinderOptional<UParticleSystem> PS_PLASMA_EXPLODE;
		FConstructorStatics() :
            PS_PLASMA(TEXT("/Game/FXVarietyPack/Particles/P_ky_waterBall")),
            PS_PLASMA_EXPLODE(TEXT("/Game/FXVarietyPack/Particles/P_ky_hit1"))
        {}
	};

	static FConstructorStatics ConstructorStatics;

    PlasmaParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PlasmaParticle"));
    PlasmaExplodeParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PlasmaExplodeParticle"));

    PlasmaParticle->SetupAttachment(RootComponent);
    PlasmaParticle->SetRelativeLocation(FVector(0.000000, 0.000000, 0.000000));
    PlasmaParticle->SetRelativeScale3D(FVector(2.000000, 2.000000, 2.000000));

    PlasmaExplodeParticle->SetupAttachment(RootComponent);
    PlasmaExplodeParticle->SetRelativeLocation(FVector(0.000000, 0.000000, 0.000000));
    PlasmaExplodeParticle->SetRelativeScale3D(FVector(2.000000, 2.000000, 2.000000));
    PlasmaExplodeParticle->SetAutoActivate(false);

    StarSizeHitPoints = (float) FMath::RandRange(2, 10);
    ObstacleMesh->SetRelativeScale3D(FVector(StarSizeHitPoints, StarSizeHitPoints, StarSizeHitPoints));
    ObstacleMesh->SetCollisionProfileName(FName("OverlapAll"));

    if (ConstructorStatics.PS_PLASMA.Get() != nullptr)
    {
        PlasmaParticle->SetTemplate(ConstructorStatics.PS_PLASMA.Get());
    }
    if (ConstructorStatics.PS_PLASMA_EXPLODE.Get() != nullptr)
    {
        PlasmaExplodeParticle->SetTemplate(ConstructorStatics.PS_PLASMA_EXPLODE.Get());
    }
}

void AStarObstacle::BeginPlay()
{
    Super::BeginPlay();

    ObstacleMesh->OnComponentBeginOverlap.AddDynamic(this, &AStarObstacle::PickUpMeshBeginOverlap);
}

void AStarObstacle::PickUpMeshBeginOverlap(class UPrimitiveComponent *OverlappedComp, class AActor *Other, class UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
    if (HitByPlayer)
        return;

    auto isPlayer = Cast<ASpaceShipPawn>(Other);

    if (isPlayer)
    {
        ObstacleMesh->SetVisibility(false);
        HitByPlayer=true;

        UE_LOG(LogTemp, Warning, TEXT("StarObstacle [ %s ]  [ %s ]  [DECREMENTO %f ]"), *isPlayer->GetName(), *FString(__func__), StarSizeHitPoints);

        isPlayer->DecrementLife(StarSizeHitPoints);
        PlasmaExplodeParticle->Activate(true);

        SetLifeSpan(0.1f);
    }
}
