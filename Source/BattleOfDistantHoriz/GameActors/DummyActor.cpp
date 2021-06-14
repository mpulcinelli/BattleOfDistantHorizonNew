// Fill out your copyright notice in the Description page of Project Settings.

#include "DummyActor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"



// Sets default values
ADummyActor::ADummyActor()
{
	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	SphereCollider->InitSphereRadius(32.0f);
	SphereCollider->BodyInstance.SetCollisionProfileName("Projectile");
	SphereCollider->OnComponentHit.AddDynamic(this, &ADummyActor::OnHit);		// set up a notification for when this component hits something blocking
	SphereCollider->bHiddenInGame=false;

	// Players can't walk on it
	SphereCollider->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	SphereCollider->CanCharacterStepUpOn = ECB_No;

	RootComponent = SphereCollider;

	ProjectileMovimentComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovimentComp"));
	ProjectileMovimentComp->UpdatedComponent = SphereCollider;
	ProjectileMovimentComp->InitialSpeed = 5000.f;
	ProjectileMovimentComp->MaxSpeed = 5000.f;
	ProjectileMovimentComp->bRotationFollowsVelocity = true;
	ProjectileMovimentComp->bShouldBounce = true;
	//ProjectileMovimentComp->Bounciness = 1.0f;
	//ProjectileMovimentComp->ProjectileGravityScale = 0.0f;

	InitialLifeSpan = 3.0f;
}

void ADummyActor::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		Destroy();
	}
}