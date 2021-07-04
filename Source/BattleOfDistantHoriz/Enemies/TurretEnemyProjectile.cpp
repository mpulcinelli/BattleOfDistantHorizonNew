// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretEnemyProjectile.h"

#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystem.h"
#include "UObject/ConstructorHelpers.h"
#include "BattleOfDistantHoriz/Characters/SpaceShipPawn.h"

// Sets default values
ATurretEnemyProjectile::ATurretEnemyProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	ProjectileParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ProjectileParticle"));
	ProjectileMovimentComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovimentComp"));

	RootComponent = SphereCollider;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS_PROJECTILE_01(TEXT("/Game/StylizedProjectiles/Particles/Projectile_06/P_Projectile_06"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS_PROJECTILE_01_HIT(TEXT("/Game/StylizedProjectiles/Particles/Projectile_06/P_Projectile_06_Hit"));

	ProjectileParticle->SetupAttachment(SphereCollider);
	ProjectileParticle->SetAutoActivate(false);

	SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &ATurretEnemyProjectile::SphereColliderBeginOverlap);
	SphereCollider->OnComponentHit.AddDynamic(this, &ATurretEnemyProjectile::OnProjectileHit);
	SphereCollider->SetHiddenInGame(true);

	SphereCollider->SetGenerateOverlapEvents(true);
	SphereCollider->SetCollisionProfileName(FName("OverlapAll"));

	SphereCollider->SetSphereRadius(32.0f);

	ProjectileMovimentComp->InitialSpeed = 10000.f;
	ProjectileMovimentComp->MaxSpeed = 15000.f;
	ProjectileMovimentComp->bRotationFollowsVelocity = false;
	ProjectileMovimentComp->bShouldBounce = false;
	ProjectileMovimentComp->ProjectileGravityScale = 0.0f;
	ProjectileMovimentComp->SetAutoActivate(false);
	ProjectileMovimentComp->SetVelocityInLocalSpace(FVector::ForwardVector * 1000.0f);

	InitialLifeSpan = 5.0f;

	if(PS_PROJECTILE_01.Object!=nullptr)
		ProjectileParticle->SetTemplate(PS_PROJECTILE_01.Object);

	if(PS_PROJECTILE_01_HIT.Object!=nullptr)
		Projectile01_Hit_Particle = PS_PROJECTILE_01_HIT.Object;

}

// Called when the game starts or when spawned
void ATurretEnemyProjectile::BeginPlay()
{
	Super::BeginPlay();

}

void ATurretEnemyProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit )
{
	UE_LOG(LogTemp, Warning, TEXT("PROJECTILE HIT %s"), *OtherActor->GetName());
}

void ATurretEnemyProjectile::SphereColliderBeginOverlap(class UPrimitiveComponent *OverlappedComp, class AActor *Other, class UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if ((Other != nullptr) && (Other != this) && (OtherComp != nullptr) && (Other->GetName().Contains("SpaceShipPawn")))
	{
		UE_LOG(LogTemp, Warning, TEXT("PROJECTILE BeginOverlap %s"), *Other->GetName());

		if (OtherComp->IsSimulatingPhysics())
		{
			OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
		}

		auto W = GetWorld();
		if (W)
		{
			UGameplayStatics::SpawnEmitterAtLocation(W, Projectile01_Hit_Particle, SweepResult.Location, SweepResult.Normal.Rotation());
		}

		auto ship = Cast<ASpaceShipPawn>(Other);

		if(ship){
			ship->DecrementLife(5.0f);
		}

		SetLifeSpan(0.1f);
	}
}

void ATurretEnemyProjectile::ExecuteFire()
{
	ProjectileParticle->Activate(true);
	ProjectileMovimentComp->SetActive(true, true);
}

