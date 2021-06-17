// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleOfDistantHoriz/Obstacles/LaserWallObstacle.h"

#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "Components/BoxComponent.h"
#include "BattleOfDistantHoriz/Characters/SpaceShipPawn.h"

ALaserWallObstacle::ALaserWallObstacle()
{
    static ConstructorHelpers::FObjectFinder<UParticleSystem> PS_LASER(TEXT("/Game/ParticleEffects/PS_RAio"));

    PrimaryActorTick.bCanEverTick = false;

    USceneComponent *RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
    RootComponent = RootComp;

    /** LASER 1 **/
    Laser_01_Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Laser_01_Particle"));
    Laser_01_Particle->SetupAttachment(RootComponent);
    Laser_01_Particle->SetRelativeLocation(FVector(0.000000, 0.000000, -1500.000000));
    Laser_01_Particle->SetRelativeScale3D(FVector(1.0, 1.0, 1.0));
    Laser_01_Particle->SetAutoActivate(false);

    Laser_01_Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Laser_01_Collision"));
    Laser_01_Collision->SetupAttachment(RootComponent);
    Laser_01_Collision->SetRelativeLocation(FVector(0.000000, 150.000000, -1500.000000));
    Laser_01_Collision->SetRelativeScale3D(FVector(1.0, 150.0, 1.0));
    Laser_01_Collision->SetCollisionProfileName("BlockAll");

    /** LASER 2 **/

    Laser_02_Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Laser_02_Particle"));
    Laser_02_Particle->SetupAttachment(RootComponent);
    Laser_02_Particle->SetRelativeLocation(FVector(0.000000, 0.000000, -1000.000000));
    Laser_02_Particle->SetRelativeScale3D(FVector(1.0, 1.0, 1.0));
    Laser_02_Particle->SetAutoActivate(false);

    Laser_02_Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Laser_02_Collision"));
    Laser_02_Collision->SetupAttachment(RootComponent);
    Laser_02_Collision->SetRelativeLocation(FVector(0.000000, 150.000000, -1000.000000));
    Laser_02_Collision->SetRelativeScale3D(FVector(1.0, 150.0, 1.0));
    Laser_02_Collision->SetCollisionProfileName("BlockAll");

    /** LASER 3 **/
    Laser_03_Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Laser_03_Particle"));
    Laser_03_Particle->SetupAttachment(RootComponent);
    Laser_03_Particle->SetRelativeLocation(FVector(0.000000, 0.000000, -500.000000));
    Laser_03_Particle->SetRelativeScale3D(FVector(1.0, 1.0, 1.0));
    Laser_03_Particle->SetAutoActivate(false);

    Laser_03_Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Laser_03_Collision"));
    Laser_03_Collision->SetupAttachment(RootComponent);
    Laser_03_Collision->SetRelativeLocation(FVector(0.000000, 150.000000, -500.000000));
    Laser_03_Collision->SetRelativeScale3D(FVector(1.0, 150.0, 1.0));
    Laser_03_Collision->SetCollisionProfileName("BlockAll");

    /** LASER 4 **/
    Laser_04_Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Laser_04_Particle"));
    Laser_04_Particle->SetupAttachment(RootComponent);
    Laser_04_Particle->SetRelativeLocation(FVector(0.000000, 0.000000, 0.000000));
    Laser_04_Particle->SetRelativeScale3D(FVector(1.0, 1.0, 1.0));
    Laser_04_Particle->SetAutoActivate(false);

    Laser_04_Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Laser_04_Collision"));
    Laser_04_Collision->SetupAttachment(RootComponent);
    Laser_04_Collision->SetRelativeLocation(FVector(0.000000, 150.000000, 0.000000));
    Laser_04_Collision->SetRelativeScale3D(FVector(1.0, 150.0, 1.0));
    Laser_04_Collision->SetCollisionProfileName("BlockAll");

    /** LASER 5 **/
    Laser_05_Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Laser_05_Particle"));
    Laser_05_Particle->SetupAttachment(RootComponent);
    Laser_05_Particle->SetRelativeLocation(FVector(0.000000, 0.000000, 500.000000));
    Laser_05_Particle->SetRelativeScale3D(FVector(1.0, 1.0, 1.0));
    Laser_05_Particle->SetAutoActivate(false);

    Laser_05_Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Laser_05_Collision"));
    Laser_05_Collision->SetupAttachment(RootComponent);
    Laser_05_Collision->SetRelativeLocation(FVector(0.000000, 150.000000, 500.000000));
    Laser_05_Collision->SetRelativeScale3D(FVector(1.0, 150.0, 1.0));
    Laser_05_Collision->SetCollisionProfileName("BlockAll");

    /** LASER 6 **/
    Laser_06_Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Laser_06_Particle"));
    Laser_06_Particle->SetupAttachment(RootComponent);
    Laser_06_Particle->SetRelativeLocation(FVector(0.000000, 0.000000, 1000.000000));
    Laser_06_Particle->SetRelativeScale3D(FVector(1.0, 1.0, 1.0));
    Laser_06_Particle->SetAutoActivate(false);

    Laser_06_Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Laser_06_Collision"));
    Laser_06_Collision->SetupAttachment(RootComponent);
    Laser_06_Collision->SetRelativeLocation(FVector(0.000000, 150.000000, 1000.000000));
    Laser_06_Collision->SetRelativeScale3D(FVector(1.0, 150.0, 1.0));
    Laser_06_Collision->SetCollisionProfileName("BlockAll");

    /** LASER 7 **/
    Laser_07_Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Laser_07_Particle"));
    Laser_07_Particle->SetupAttachment(RootComponent);
    Laser_07_Particle->SetRelativeLocation(FVector(0.000000, 0.000000, 1500.000000));
    Laser_07_Particle->SetRelativeScale3D(FVector(1.0, 1.0, 1.0));
    Laser_07_Particle->SetAutoActivate(false);

    Laser_07_Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Laser_07_Collision"));
    Laser_07_Collision->SetupAttachment(RootComponent);
    Laser_07_Collision->SetRelativeLocation(FVector(0.000000, 150.000000, 1500.000000));
    Laser_07_Collision->SetRelativeScale3D(FVector(1.0, 150.0, 1.0));
    Laser_07_Collision->SetCollisionProfileName("BlockAll");

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

    Laser_01_Collision->OnComponentHit.AddDynamic(this, &ALaserWallObstacle::OnHitLaser);
    Laser_02_Collision->OnComponentHit.AddDynamic(this, &ALaserWallObstacle::OnHitLaser);
    Laser_03_Collision->OnComponentHit.AddDynamic(this, &ALaserWallObstacle::OnHitLaser);
    Laser_04_Collision->OnComponentHit.AddDynamic(this, &ALaserWallObstacle::OnHitLaser);
    Laser_05_Collision->OnComponentHit.AddDynamic(this, &ALaserWallObstacle::OnHitLaser);
    Laser_06_Collision->OnComponentHit.AddDynamic(this, &ALaserWallObstacle::OnHitLaser);
    Laser_07_Collision->OnComponentHit.AddDynamic(this, &ALaserWallObstacle::OnHitLaser);

    if (FMath::RandBool())
    {
        Laser_01_Particle->Activate();
        Laser_01_Collision->SetCollisionProfileName("BlockAll");
    }
    else
    {
        Laser_01_Particle->Deactivate();
        Laser_01_Collision->SetCollisionProfileName("NoCollision");
    }

    if (FMath::RandBool())
    {
        Laser_02_Particle->Activate();
        Laser_02_Collision->SetCollisionProfileName("BlockAll");
    }
    else
    {
        Laser_02_Particle->Deactivate();
        Laser_02_Collision->SetCollisionProfileName("NoCollision");
    }

    if (FMath::RandBool())
    {
        Laser_03_Particle->Activate();
        Laser_03_Collision->SetCollisionProfileName("BlockAll");
    }
    else
    {
        Laser_03_Particle->Deactivate();
        Laser_03_Collision->SetCollisionProfileName("NoCollision");
    }

    if (FMath::RandBool())
    {
        Laser_04_Particle->Activate();
        Laser_04_Collision->SetCollisionProfileName("BlockAll");
    }
    else
    {
        Laser_04_Particle->Deactivate();
        Laser_04_Collision->SetCollisionProfileName("NoCollision");
    }

    if (FMath::RandBool())
    {
        Laser_05_Particle->Activate();
        Laser_05_Collision->SetCollisionProfileName("BlockAll");
    }
    else
    {
        Laser_05_Particle->Deactivate();
        Laser_05_Collision->SetCollisionProfileName("NoCollision");
    }

    if (FMath::RandBool())
    {
        Laser_06_Particle->Activate();
        Laser_06_Collision->SetCollisionProfileName("BlockAll");
    }
    else
    {
        Laser_06_Particle->Deactivate();
        Laser_06_Collision->SetCollisionProfileName("NoCollision");
    }

    if (FMath::RandBool())
    {
        Laser_07_Particle->Activate();
        Laser_07_Collision->SetCollisionProfileName("BlockAll");
    }
    else
    {
        Laser_07_Particle->Deactivate();
        Laser_07_Collision->SetCollisionProfileName("NoCollision");
    }
}

void ALaserWallObstacle::OnHitLaser(UPrimitiveComponent *HitComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit)
{
    auto isPlayer = Cast<ASpaceShipPawn>(OtherActor);

    if (isPlayer)
    {
        
        FString particle = HitComp->GetName();

        particle.RemoveAt(0, 6);
        particle.RemoveAt(2, 10);
        
        int32 selectedParticle = FCString::Atoi(*particle);
        
        switch (selectedParticle)
        {
        case 1:
            Laser_01_Particle->DestroyComponent();
            break;
        case 2:
            Laser_02_Particle->DestroyComponent();
            break;
        case 3:
            Laser_03_Particle->DestroyComponent();
            break;
        case 4:
            Laser_04_Particle->DestroyComponent();
            break;
        case 5:
            Laser_05_Particle->DestroyComponent();
            break;
        case 6:
            Laser_06_Particle->DestroyComponent();
            break;
        case 7:
            Laser_07_Particle->DestroyComponent();
            break;
        default:
            break;
        }

        HitComp->DestroyComponent();

        isPlayer->DecrementLife(5.0f);
    }
}