// Fill out your copyright notice in the Description page of Project Settings.

#include "StarObstacle.h"
#include "UObject/ConstructorHelpers.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "BattleOfDistantHoriz/Characters/SpaceShipPawn.h"

AStarObstacle::AStarObstacle()
{
    static ConstructorHelpers::FObjectFinder<UParticleSystem> PS_PLASMA(TEXT("/Game/FXVarietyPack/Particles/P_ky_waterBall"));
    static ConstructorHelpers::FObjectFinder<UParticleSystem> PS_PLASMA_EXPLODE(TEXT("/Game/FXVarietyPack/Particles/P_ky_waterBallHit"));

    PlasmaParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PlasmaParticle"));
    PlasmaExplodeParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PlasmaExplodeParticle"));

    PlasmaParticle->SetupAttachment(RootComponent);
    PlasmaParticle->SetRelativeLocation(FVector(0.000000, 0.000000, 0.000000));
    PlasmaParticle->SetRelativeScale3D(FVector(2.000000, 2.000000, 2.000000));

    PlasmaExplodeParticle->SetupAttachment(RootComponent);
    PlasmaExplodeParticle->SetRelativeLocation(FVector(0.000000, 0.000000, 0.000000));
    PlasmaExplodeParticle->SetRelativeScale3D(FVector(2.000000, 2.000000, 2.000000));
    PlasmaExplodeParticle->SetAutoActivate(false);

    PickUpMesh->SetRelativeScale3D(FVector(2.000000, 2.000000, 2.000000));
    PickUpMesh->SetCollisionProfileName(FName("OverlapAll"));

    if (PS_PLASMA.Object != nullptr)
    {
        PlasmaParticle->SetTemplate(PS_PLASMA.Object);
    }
    if (PS_PLASMA_EXPLODE.Object != nullptr)
    {
        PlasmaExplodeParticle->SetTemplate(PS_PLASMA_EXPLODE.Object);
    }
}


void AStarObstacle::BeginPlay()
{
    Super::BeginPlay();

    PickUpMesh->OnComponentBeginOverlap.AddDynamic(this, &AStarObstacle::PickUpMeshBeginOverlap);
}

void AStarObstacle::PickUpMeshBeginOverlap(class UPrimitiveComponent *OverlappedComp, class AActor *Other, class UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
    auto isPlayer = Cast<ASpaceShipPawn>(Other);

    if(isPlayer)
    {
        isPlayer->DecrementLife(5.0f);
        PlasmaExplodeParticle->Activate();
    }
}

