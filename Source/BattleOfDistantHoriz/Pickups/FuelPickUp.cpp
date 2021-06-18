#include "BattleOfDistantHoriz/Pickups/FuelPickUp.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Components/RectLightComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "BattleOfDistantHoriz/Characters/SpaceShipPawn.h"

AFuelPickUp::AFuelPickUp(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
    static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_PICK_UP(TEXT("/Game/Geometry/Meshes/BatteryPickup/BatteryPickUp"));
    static ConstructorHelpers::FObjectFinder<UParticleSystem> PS_LIGHTNING(TEXT("/Game/FXVarietyPack/Particles/P_ky_lightning2"));
    //static ConstructorHelpers::FObjectFinder<UParticleSystem> PS_FUEL_CONSUMED(TEXT("/Game/FXVarietyPack/Particles/P_ky_hit2"));
    static ConstructorHelpers::FObjectFinder<UParticleSystem> PS_FUEL_CONSUMED(TEXT("/Game/FXVarietyPack/Particles/P_ky_shotShockwave"));
    
    TopLigh = CreateDefaultSubobject<URectLightComponent>(TEXT("TopLigh"));
    BoltParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("BoltParticle"));
    FuelTankRotation = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("FuelTankRotation"));
    FuelConsumedParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FuelConsumedParticle"));

    PickUpMesh->SetMobility(EComponentMobility::Movable);

    FuelTankRotation->RotationRate = FRotator(30.0f, 50.0f, 100.0f);

    BoltParticle->SetupAttachment(RootComponent);
    BoltParticle->SetRelativeLocation(FVector(0.000000, 0.000000, 420.000000));
    BoltParticle->SetRelativeScale3D(FVector(2.000000,2.000000,2.000000));

    FuelConsumedParticle->SetupAttachment(RootComponent);
    FuelConsumedParticle->SetRelativeLocation(FVector(0.000000, 0.000000, 420.000000));
    FuelConsumedParticle->SetRelativeScale3D(FVector(4.000000,4.000000,4.000000));
    FuelConsumedParticle->SetAutoActivate(false);

    TopLigh->SetupAttachment(RootComponent);
    TopLigh->SetRelativeLocation(FVector(0.000000, 0.000000, 880.000000));
    TopLigh->SetIntensity(100000.0);
    TopLigh->SetLightColor(FLinearColor::Yellow);
    TopLigh->SetRelativeRotation(FRotator(-90.000000, 180.000000, 180.000000));

    PickUpMesh->SetCollisionProfileName(FName("OverlapAll"));
    QuantidadeCarga = FMath::RandRange(1.0f, 100.0f);

    if (PS_FUEL_CONSUMED.Object != nullptr)
    {
        FuelConsumedParticle->SetTemplate(PS_FUEL_CONSUMED.Object);
    }

    if (PS_LIGHTNING.Object != nullptr)
    {
        BoltParticle->SetTemplate(PS_LIGHTNING.Object);
    }


    if (SM_PICK_UP.Object != nullptr)
    {
        PickUpMesh->SetStaticMesh(SM_PICK_UP.Object);
    }
}

void AFuelPickUp::BeginPlay()
{
    Super::BeginPlay();

    PickUpMesh->OnComponentBeginOverlap.AddDynamic(this, &AFuelPickUp::PickUpMeshBeginOverlap);
    BoltParticle->OnSystemFinished.AddDynamic(this, &AFuelPickUp::BoltParticleFinished);

    GetWorld()->GetTimerManager().SetTimer(TriggerBoltTimerHandle, this, &AFuelPickUp::TriggerBoltParticle, TimeToRepeatBolt(QuantidadeCarga), true, 0);
}


void AFuelPickUp::PickUpMeshBeginOverlap(class UPrimitiveComponent *OverlappedComp, class AActor *Other, class UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
    if (bUsedCharge)
        return;

    auto isPlayer = Cast<ASpaceShipPawn>(Other);
    if (isPlayer != nullptr)
    {
        PickUpMesh->SetVisibility(false);
        bUsedCharge = true;
        isPlayer->AddFuel(QuantidadeCarga);
        FuelConsumedParticle->Activate();
        SetLifeSpan(0.5f);
    }
}

void AFuelPickUp::BoltParticleFinished(class UParticleSystemComponent* PSystem) 
{
    UE_LOG(LogTemp, Warning, TEXT("BoltParticleFinished"));
}

void AFuelPickUp::TriggerBoltParticle() 
{
    BoltParticle->Deactivate();
    BoltParticle->Activate();
    UE_LOG(LogTemp, Warning, TEXT("TriggerBoltParticle - %s"), *this->GetName());
}
