#include "BattleOfDistantHoriz/Pickups/FuelPickUp.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Components/RectLightComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "BattleOfDistantHoriz/Characters/SpaceShipPawn.h"

AFuelPickUp::AFuelPickUp(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
	struct FConstructorStatics
	{
        ConstructorHelpers::FObjectFinderOptional<UStaticMesh>     SM_PICK_UP;
        ConstructorHelpers::FObjectFinderOptional<UParticleSystem> PS_LIGHTNING;
        ConstructorHelpers::FObjectFinderOptional<UParticleSystem> PS_FUEL_CONSUMED;
        ConstructorHelpers::FObjectFinderOptional<USoundCue> CUE_BOLT_SOUND;
		FConstructorStatics() :
            SM_PICK_UP(TEXT("/Game/Geometry/Meshes/BatteryPickup/BatteryPickUp")),
            PS_LIGHTNING(TEXT("/Game/FXVarietyPack/Particles/P_ky_lightning2")),
            PS_FUEL_CONSUMED(TEXT("/Game/FXVarietyPack/Particles/P_ky_shotShockwave")),
            CUE_BOLT_SOUND(TEXT("/Game/Audio/energy-bounce_au_Cue"))
        {}
	};

	static FConstructorStatics ConstructorStatics;

    TopLigh = CreateDefaultSubobject<URectLightComponent>(TEXT("TopLigh"));
    BoltParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("BoltParticle"));
    FuelTankRotation = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("FuelTankRotation"));
    FuelConsumedParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FuelConsumedParticle"));
    AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));


    AudioComponent->SetupAttachment(RootComponent);
    AudioComponent->SetAutoActivate(false);

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

    if(ConstructorStatics.CUE_BOLT_SOUND.Get()!=nullptr){
        AudioComponent->SetSound(ConstructorStatics.CUE_BOLT_SOUND.Get());
    }


    if (ConstructorStatics.PS_FUEL_CONSUMED.Get() != nullptr)
    {
        FuelConsumedParticle->SetTemplate(ConstructorStatics.PS_FUEL_CONSUMED.Get());
    }

    if (ConstructorStatics.PS_LIGHTNING.Get() != nullptr)
    {
        BoltParticle->SetTemplate(ConstructorStatics.PS_LIGHTNING.Get());
    }


    if (ConstructorStatics.SM_PICK_UP.Get() != nullptr)
    {
        PickUpMesh->SetStaticMesh(ConstructorStatics.SM_PICK_UP.Get());
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

    if (auto isPlayer = Cast<ASpaceShipPawn>(Other))
    {
        bUsedCharge = true;
        PickUpMesh->SetVisibility(false);
        isPlayer->AddFuel(QuantidadeCarga);
        FuelConsumedParticle->Activate();
        SetLifeSpan(0.1f);
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
    AudioComponent->Play();
    UE_LOG(LogTemp, Warning, TEXT("TriggerBoltParticle - %s"), *this->GetName());
}
