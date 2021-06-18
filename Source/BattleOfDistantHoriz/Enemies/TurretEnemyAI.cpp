// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleOfDistantHoriz/Enemies/TurretEnemyAI.h"
//#include "Perception/AIPerceptionComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "Engine/SkeletalMesh.h"

// Sets default values
ATurretEnemyAI::ATurretEnemyAI()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_TURRET(TEXT("/Game/untitled_category/treco"));

	//AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
	AISensing =  CreateDefaultSubobject<UPawnSensingComponent>(TEXT("AISensing"));
	AISensing->HearingThreshold = 500.0f;
	AISensing->LOSHearingThreshold = 1200.0f;
	AISensing->SightRadius = 700.0f;
	AISensing->SensingInterval = 0.5f;
	AISensing->SetPeripheralVisionAngle(55.0f);

	if(SK_TURRET.Object!=nullptr){
		GetMesh()->SetSkeletalMesh(SK_TURRET.Object);
	}
}

// Called when the game starts or when spawned
void ATurretEnemyAI::BeginPlay()
{
	Super::BeginPlay();

	AISensing->OnSeePawn.AddDynamic(this, &ATurretEnemyAI::OnSeePawnByAi);
}

void ATurretEnemyAI::OnSeePawnByAi(APawn* Pawn)
{
	UE_LOG(LogTemp, Warning, TEXT("POSICAO DO PLAYER: %s"), *Pawn->GetActorLocation().ToString());
}

// Called every frame
void ATurretEnemyAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
