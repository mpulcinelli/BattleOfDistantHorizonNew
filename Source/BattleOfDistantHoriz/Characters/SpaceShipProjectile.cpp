// Fill out your copyright notice in the Description page of Project Settings.

#include "SpaceShipProjectile.h"
#include "SpaceShipPawn.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystem.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
ASpaceShipProjectile::ASpaceShipProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	ProjectileParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ProjectileParticle"));
	ProjectileMovimentComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovimentComp"));

	RootComponent = SphereCollider;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS_PROJECTILE_01(TEXT("/Game/StylizedProjectiles/Particles/Projectile_01/P_Projectile_01"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS_PROJECTILE_01_HIT(TEXT("/Game/StylizedProjectiles/Particles/Projectile_01/P_Projectile_01_Hit"));

	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS_PROJECTILE_02(TEXT("/Game/StylizedProjectiles/Particles/Projectile_09/P_Projectile_09"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS_PROJECTILE_02_HIT(TEXT("/Game/StylizedProjectiles/Particles/Projectile_09/P_Projectile_09_Hit"));

	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS_PROJECTILE_03(TEXT("/Game/StylizedProjectiles/Particles/Projectile_03/P_Projectile_03"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS_PROJECTILE_03_HIT(TEXT("/Game/StylizedProjectiles/Particles/Projectile_03/P_Projectile_03_Hit"));

	ProjectileParticle->SetupAttachment(SphereCollider);

	SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &ASpaceShipProjectile::SphereColliderBeginOverlap);
	SphereCollider->SetHiddenInGame(true);

	SphereCollider->SetGenerateOverlapEvents(true);
	SphereCollider->SetCollisionProfileName(FName("ProjectileProfile"));
	SphereCollider->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);

	SphereCollider->SetSphereRadius(32.0f);

	ProjectileMovimentComp->InitialSpeed = 5000.f;
	ProjectileMovimentComp->MaxSpeed = 15000.f;
	ProjectileMovimentComp->bRotationFollowsVelocity = false;
	ProjectileMovimentComp->bShouldBounce = false;
	ProjectileMovimentComp->ProjectileGravityScale = 0.0f;
	ProjectileMovimentComp->SetAutoActivate(false);
	ProjectileMovimentComp->SetVelocityInLocalSpace(FVector::ForwardVector * 1000.0f);

	if (PS_PROJECTILE_01.Object != nullptr)
	{
		auto val = PS_PROJECTILE_01.Object;
		Particles.Add(val);
	}

	if (PS_PROJECTILE_01_HIT.Object != nullptr)
	{
		auto val = PS_PROJECTILE_01_HIT.Object;
		Particles.Add(val);
	}

	if (PS_PROJECTILE_02.Object != nullptr)
	{
		auto val = PS_PROJECTILE_02.Object;
		Particles.Add(val);
	}

	if (PS_PROJECTILE_02_HIT.Object != nullptr)
	{
		auto val = PS_PROJECTILE_02_HIT.Object;
		Particles.Add(val);
	}

	if (PS_PROJECTILE_03.Object != nullptr)
	{
		auto val = PS_PROJECTILE_03.Object;
		Particles.Add(val);
	}

	if (PS_PROJECTILE_03_HIT.Object != nullptr)
	{
		auto val = PS_PROJECTILE_03_HIT.Object;
		Particles.Add(val);
	}

	InitialLifeSpan = 5.0f;
}

// Called when the game starts or when spawned
void ASpaceShipProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void ASpaceShipProjectile::SphereColliderBeginOverlap(class UPrimitiveComponent *OverlappedComp, class AActor *Other, class UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{

	if ((Other != nullptr) && (Other != this) && (OtherComp != nullptr) && (!Other->GetName().Contains("SpaceShipPawn")))
	{
		UE_LOG(LogTemp, Warning, TEXT("PROJECTILE BeginOverlap %s"), *Other->GetName());

		if (OtherComp->IsSimulatingPhysics())
		{
			OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
		}

		auto W = GetWorld();
		if (W)
		{
			UGameplayStatics::SpawnEmitterAtLocation(W, Particles[SelectedPosition + 1], SweepResult.Location, SweepResult.Normal.Rotation());
		}

		SetLifeSpan(0.5);
	}
}

void ASpaceShipProjectile::ExecuteFire(int Pos = 0)
{
	SelectedPosition = Pos;
	ProjectileParticle->SetTemplate(Particles[SelectedPosition]);
	ProjectileMovimentComp->SetActive(true, true);
}
