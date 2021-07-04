// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleOfDistantHoriz/Enemies/TurretEnemyAI.h"
#include "Perception/PawnSensingComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Engine/SkeletalMesh.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"
#include "Components/CapsuleComponent.h"
#include "BattleOfDistantHoriz/Enemies/TurretEnemyProjectile.h"

// Sets default values
ATurretEnemyAI::ATurretEnemyAI()
{

	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<USkeletalMesh> SKT_TURRET;
		FConstructorStatics() : SKT_TURRET(TEXT("/Game/Inimigo/Meshes/treco.treco")) {}
	};

	static FConstructorStatics ConstructorStatics;

	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//
	//static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_TURRET(TEXT("/Game/Inimigo/Meshes/treco"));

	GetMesh()->SetSkeletalMesh(ConstructorStatics.SKT_TURRET.Get());
	GetCapsuleComponent()->SetMobility(EComponentMobility::Static);

	this->AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;


	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));
	PawnSensing->SetPeripheralVisionAngle(30.0f);
	PawnSensing->SightRadius = 20000.0f;
	PawnSensing->SetSensingUpdatesEnabled(true);
	PawnSensing->bSeePawns = true;
	PawnSensing->bOnlySensePlayers = true;
}

void ATurretEnemyAI::FireSelection(FVector Loc, FRotator Rot)
{
	FActorSpawnParameters SpawnInfo;

	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	auto W = GetWorld();
	if (W != nullptr)
	{
		auto projectile = GetWorld()->SpawnActor<ATurretEnemyProjectile>(Loc, Rot, SpawnInfo);
		if (projectile)
		{
			UE_LOG(LogTemp, Warning, TEXT("FireSelection"));
			projectile->ExecuteFire();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("INVALIDO PROJECTILE"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("INVALIDO WORLD"));
	}
}

// Called when the game starts or when spawned
void ATurretEnemyAI::BeginPlay()
{
	Super::BeginPlay();
	PawnSensing->OnSeePawn.AddDynamic(this, &ATurretEnemyAI::OnSeePawnByAi);
}

void ATurretEnemyAI::OnSeePawnByAi(APawn *SeenPawn)
{
	//DrawDebugLine(GetWorld(), this->GetActorLocation(), SeenPawn->GetActorLocation(), FColor::Red, false, 10.0f);
	auto TargetRot = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), SeenPawn->GetActorLocation());
	FireSelection(this->GetActorLocation(), TargetRot);
}

void ATurretEnemyAI::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ATurretEnemyAI::SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}