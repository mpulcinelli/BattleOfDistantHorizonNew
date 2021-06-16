// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleOfDistantHoriz/Obstacles/LaserWallObstacle.h"

#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"

ALaserWallObstacle::ALaserWallObstacle()
{
    static ConstructorHelpers::FObjectFinder<UParticleSystem> PS_LASER(TEXT("/Game/ParticleEffects/PS_RAio"));

    PrimaryActorTick.bCanEverTick = false;

    USceneComponent *RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
    RootComponent = RootComp;

    Laser_01_Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Laser_01_Particle"));
    Laser_01_Particle->SetupAttachment(RootComponent);
    Laser_01_Particle->SetRelativeLocation(FVector(0.000000, 0.000000, -1500.000000));
    Laser_01_Particle->SetRelativeScale3D(FVector(2.000000, 2.000000, 2.000000));
    Laser_01_Particle->SetAutoActivate(false);

    Laser_02_Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Laser_02_Particle"));
    Laser_02_Particle->SetupAttachment(RootComponent);
    Laser_02_Particle->SetRelativeLocation(FVector(0.000000, 0.000000, -1000.000000));
    Laser_02_Particle->SetRelativeScale3D(FVector(2.000000, 2.000000, 2.000000));
    Laser_02_Particle->SetAutoActivate(false);

    Laser_03_Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Laser_03_Particle"));
    Laser_03_Particle->SetupAttachment(RootComponent);
    Laser_03_Particle->SetRelativeLocation(FVector(0.000000, 0.000000, -500.000000));
    Laser_03_Particle->SetRelativeScale3D(FVector(2.000000, 2.000000, 2.000000));
    Laser_03_Particle->SetAutoActivate(false);

    Laser_04_Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Laser_04_Particle"));
    Laser_04_Particle->SetupAttachment(RootComponent);
    Laser_04_Particle->SetRelativeLocation(FVector(0.000000, 0.000000, 0.000000));
    Laser_04_Particle->SetRelativeScale3D(FVector(2.000000, 2.000000, 2.000000));
    Laser_04_Particle->SetAutoActivate(false);


    Laser_05_Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Laser_05_Particle"));
    Laser_05_Particle->SetupAttachment(RootComponent);
    Laser_05_Particle->SetRelativeLocation(FVector(0.000000, 0.000000, 500.000000));
    Laser_05_Particle->SetRelativeScale3D(FVector(2.000000, 2.000000, 2.000000));
    Laser_05_Particle->SetAutoActivate(false);

    Laser_06_Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Laser_06_Particle"));
    Laser_06_Particle->SetupAttachment(RootComponent);
    Laser_06_Particle->SetRelativeLocation(FVector(0.000000, 0.000000, 1000.000000));
    Laser_06_Particle->SetRelativeScale3D(FVector(2.000000, 2.000000, 2.000000));
    Laser_06_Particle->SetAutoActivate(false);

    Laser_07_Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Laser_07_Particle"));
    Laser_07_Particle->SetupAttachment(RootComponent);
    Laser_07_Particle->SetRelativeLocation(FVector(0.000000, 0.000000, 1500.000000));
    Laser_07_Particle->SetRelativeScale3D(FVector(2.000000, 2.000000, 2.000000));
    Laser_07_Particle->SetAutoActivate(false);

    if (PS_LASER.Object != nullptr)
    {
        Laser_01_Particle->SetTemplate(PS_LASER.Object);
        Laser_02_Particle->SetTemplate(PS_LASER.Object);
        Laser_03_Particle->SetTemplate(PS_LASER.Object);
        Laser_04_Particle->SetTemplate(PS_LASER.Object);
        Laser_05_Particle->SetTemplate(PS_LASER.Object);
        Laser_06_Particle->SetTemplate(PS_LASER.Object);
        Laser_07_Particle->SetTemplate(PS_LASER.Object);
    }
}

void ALaserWallObstacle::BeginPlay()
{
    Super::BeginPlay();

    if(FMath::RandBool())
        Laser_01_Particle->Activate();
    else
        Laser_01_Particle->Deactivate();

    if(FMath::RandBool())
        Laser_02_Particle->Activate();
    else
        Laser_02_Particle->Deactivate();

    if(FMath::RandBool())
        Laser_03_Particle->Activate();
    else
        Laser_03_Particle->Deactivate();

    if(FMath::RandBool())
        Laser_04_Particle->Activate();
    else
        Laser_04_Particle->Deactivate();

    if(FMath::RandBool())
        Laser_05_Particle->Activate();
    else
        Laser_05_Particle->Deactivate();

    if(FMath::RandBool())
        Laser_06_Particle->Activate();
    else
        Laser_06_Particle->Deactivate();

    if(FMath::RandBool())
        Laser_07_Particle->Activate();
    else
        Laser_07_Particle->Deactivate();

}