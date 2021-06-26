#include "TunnelUnit.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "BattleOfDistantHoriz/Characters/SpaceShipPawn.h"
#include "Kismet/KismetMathLibrary.h"
#include "BattleOfDistantHoriz/Pickups/StarPickUp.h"
#include "BattleOfDistantHoriz/Pickups/FuelPickUp.h"
#include "Components/PointLightComponent.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BattleOfDistantHoriz/GameActors/TunnelGenerator.h"
#include "BattleOfDistantHoriz/Obstacles/LaserWallObstacle.h"
#include "BattleOfDistantHoriz/Enemies/TurretEnemyAI.h"

// Sets default values
ATunnelUnit::ATunnelUnit()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent *RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	TunnelUnitMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TunnelUnitMesh"));
	EndTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("EndTrigger"));
	AreaToSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("AreaToSpawn"));
	AreaToSpawnFuelPickUp = CreateDefaultSubobject<UBoxComponent>(TEXT("AreaToSpawnFuelPickUp"));
	AreaToSpawnTurret = CreateDefaultSubobject<UBoxComponent>(TEXT("AreaToSpawnTurret"));
	PoitLight01 = CreateDefaultSubobject<UPointLightComponent>(TEXT("PoitLight01"));
	PoitLight02 = CreateDefaultSubobject<UPointLightComponent>(TEXT("PoitLight02"));
	PoitLight03 = CreateDefaultSubobject<UPointLightComponent>(TEXT("PoitLight03"));
	PoitLight04 = CreateDefaultSubobject<UPointLightComponent>(TEXT("PoitLight04"));
	PoitLight05 = CreateDefaultSubobject<UPointLightComponent>(TEXT("PoitLight05"));
	ArrowPositionNextBlock = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowPositionNextBlock"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_TUNNEL_UNIT_OPEN(TEXT("/Game/Geometry/Meshes/SM_Tunnel_Open_4800"));
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_TUNNEL_UNIT_OPEN(TEXT("/Game/Geometry/Meshes/Tunnel_Reto_4800"));

	RootComponent = RootComp;

	TunnelUnitMesh->SetupAttachment(RootComp);
	EndTrigger->SetupAttachment(RootComp);
	AreaToSpawn->SetupAttachment(RootComp);
	AreaToSpawnFuelPickUp->SetupAttachment(RootComp);
	AreaToSpawnTurret->SetupAttachment(RootComp);

	TunnelUnitMesh->SetCollisionProfileName(FName("BlockAll"));

	PoitLight01->SetupAttachment(RootComp);
	PoitLight02->SetupAttachment(RootComp);
	PoitLight03->SetupAttachment(RootComp);
	PoitLight04->SetupAttachment(RootComp);
	PoitLight05->SetupAttachment(RootComp);

	PoitLight01->SetRelativeLocation(FVector(-1230.000000, 2270.0, 0.000000));
	PoitLight02->SetRelativeLocation(FVector(1230.000000, 2270.0, 0.000000));
	PoitLight03->SetRelativeLocation(FVector(1230.000000, -2270.0, 0.000000));
	PoitLight04->SetRelativeLocation(FVector(-1230.000000, -2270.0, 0.000000));
	PoitLight05->SetRelativeLocation(FVector(0.000000, 10.000000, 2170.000000));

	PoitLight01->SetIntensity(100000.0);
	PoitLight02->SetIntensity(100000.0);
	PoitLight03->SetIntensity(100000.0);
	PoitLight04->SetIntensity(100000.0);
	PoitLight05->SetIntensity(100000.0);

	PoitLight01->SetVisibility(false);
	PoitLight02->SetVisibility(false);
	PoitLight03->SetVisibility(false);
	PoitLight04->SetVisibility(false);
	PoitLight05->SetVisibility(false);

	PoitLight01->SetAttenuationRadius(16000.0);
	PoitLight02->SetAttenuationRadius(16000.0);
	PoitLight03->SetAttenuationRadius(16000.0);
	PoitLight04->SetAttenuationRadius(16000.0);
	PoitLight05->SetAttenuationRadius(16000.0);

	PoitLight01->SetSourceRadius(2300.0);
	PoitLight02->SetSourceRadius(2300.0);
	PoitLight03->SetSourceRadius(2300.0);
	PoitLight04->SetSourceRadius(2300.0);
	PoitLight05->SetSourceRadius(2300.0);

	PoitLight01->SetSoftSourceRadius(1500.0);
	PoitLight02->SetSoftSourceRadius(1500.0);
	PoitLight03->SetSoftSourceRadius(1500.0);
	PoitLight04->SetSoftSourceRadius(1500.0);
	PoitLight05->SetSoftSourceRadius(1500.0);

	PoitLight01->SetSourceLength(2000.0);
	PoitLight02->SetSourceLength(2000.0);
	PoitLight03->SetSourceLength(2000.0);
	PoitLight04->SetSourceLength(2000.0);
	PoitLight05->SetSourceLength(2000.0);

	PoitLight01->SetMobility(EComponentMobility::Stationary);
	PoitLight02->SetMobility(EComponentMobility::Stationary);
	PoitLight03->SetMobility(EComponentMobility::Stationary);
	PoitLight04->SetMobility(EComponentMobility::Stationary);
	PoitLight05->SetMobility(EComponentMobility::Stationary);

	EndTrigger->SetRelativeLocation(FVector(2338.0f, 0.0f, 0.0f));
	EndTrigger->SetRelativeScale3D(FVector(10.0f, 70.0f, 70.0f));
	EndTrigger->SetGenerateOverlapEvents(true);
	EndTrigger->SetCollisionProfileName(FName("BoxEndTriggerProfile"));

	AreaToSpawn->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	AreaToSpawn->SetRelativeScale3D(FVector(70.0f, 70.0f, 70.0f));
	AreaToSpawn->SetGenerateOverlapEvents(true);
	AreaToSpawn->SetCollisionProfileName(FName("BoxSpawnProfile"));

	AreaToSpawnFuelPickUp->SetRelativeLocation(FVector(0.000000, 0.000000, 0.000000));
	AreaToSpawnFuelPickUp->SetRelativeScale3D(FVector(70.0, 45.0, 50.0));
	AreaToSpawnFuelPickUp->SetGenerateOverlapEvents(false);
	AreaToSpawnFuelPickUp->SetCollisionProfileName(FName("BoxSpawnFuelProfile"));

	AreaToSpawnTurret->SetRelativeLocation(FVector(1270.000000,0.000000,-2240.000000));
	AreaToSpawnTurret->SetRelativeScale3D(FVector(30.0, 45.0, 1.0));
	AreaToSpawnTurret->SetGenerateOverlapEvents(false);
	AreaToSpawnTurret->SetCollisionProfileName(FName("BoxSpawnFuelProfile"));

	ArrowPositionNextBlock->SetRelativeLocation(FVector(2400.000000, 0.000000, -2400.000000));
	ArrowPositionNextBlock->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));

	if (SM_TUNNEL_UNIT_OPEN.Object != nullptr)
	{
		TunnelUnitMesh->SetStaticMesh(SM_TUNNEL_UNIT_OPEN.Object);
	}
}

void ATunnelUnit::BeginPlay()
{
	Super::BeginPlay();
	ShuffleLight(FMath::RandRange(0, 1));

	EndTrigger->OnComponentBeginOverlap.AddDynamic(this, &ATunnelUnit::EndTriggerBeginOverlap);

	// 20% de probabilidade de executar
	if (FMath::RandRange(1, 5) == 3)
	{
		short int qtd_estrelas = FMath::RandRange(0, 5);

		for (short int i = 0; i < qtd_estrelas; i++)
		{
			AddPickUpStar();
		}
	}

	// 10% de probabilidade de executar
	if (FMath::RandRange(1, 10) == 5)
	{
		AddPickUpFuel();
	}

	if (FMath::RandRange(1, FMath::RandRange(5, 15)) == 10)
	{
		AddLaserWall();
	}

	//AddEnemyTurret();
}

void ATunnelUnit::BeginDestroy()
{
	Super::BeginDestroy();
}

void ATunnelUnit::AddPickUpFuel()
{
	FVector RandPointToFuel;
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	FRotator RotationToSpawn = FRotator(0.0f);

	GetRandomPointIn3DBoxSpace(RandPointToFuel, AreaToSpawnFuelPickUp);

	auto fuel = GetWorld()->SpawnActor<AFuelPickUp>(RandPointToFuel, RotationToSpawn, SpawnInfo);

	if (fuel != nullptr)
	{
		ListOfCreatedActors.Add(fuel);

		fuel->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	}
}

void ATunnelUnit::AddEnemyTurret()
{
	FVector RandPointToTurret;
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	FRotator RotationToSpawn = FRotator(0.0f);

	GetRandomPointIn3DBoxSpace(RandPointToTurret, AreaToSpawnTurret);

	auto turret = GetWorld()->SpawnActor<ATurretEnemyAI>(RandPointToTurret, RotationToSpawn, SpawnInfo);

	if (turret != nullptr)
	{
		ListOfCreatedActors.Add(turret);
		UE_LOG(LogTemp, Warning, TEXT("AddEnemyTurret"));

		turret->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	}
}


void ATunnelUnit::AddPickUpStar()
{
	FVector RandPoint;

	GetRandomPointIn3DBoxSpace(RandPoint, AreaToSpawn);

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FRotator RotationToSpawn;

	auto start = GetWorld()->SpawnActor<AStarPickUp>(RandPoint, RotationToSpawn, SpawnInfo);

	if (start != nullptr)
	{
		ListOfCreatedActors.Add(start);

		start->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	}
}

void ATunnelUnit::AddLaserWall()
{
	FVector PointToSpawn = FVector(0.0, 0.0, 0.0);
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	FRotator RotationToSpawn = FRotator(0.0f);

	PointToSpawn.X = AreaToSpawnFuelPickUp->GetComponentLocation().X;
	PointToSpawn.Y = AreaToSpawnFuelPickUp->GetComponentLocation().Y;

	UE_LOG(LogTemp, Warning, TEXT("AddLaserWall:: %s"), *AreaToSpawnFuelPickUp->GetComponentLocation().ToString());

	auto wall = GetWorld()->SpawnActor<ALaserWallObstacle>(PointToSpawn, RotationToSpawn, SpawnInfo);

	if (wall != nullptr)
	{
		ListOfCreatedActors.Add(wall);

		wall->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	}
}

void ATunnelUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATunnelUnit::EndTriggerBeginOverlap(class UPrimitiveComponent *OverlappedComp, class AActor *Other, class UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (bIsPendingKill)
		return;

	auto isPlayer = Cast<ASpaceShipPawn>(Other);

	if (isPlayer != nullptr)
	{

		TArray<AActor *> TunnelGeneratorList;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATunnelGenerator::StaticClass(), TunnelGeneratorList);

		if (TunnelGeneratorList.Num() > 0)
		{
			auto TunnelGenerator = Cast<ATunnelGenerator>(TunnelGeneratorList[0]);
			TunnelGenerator->CreateUnit();
		}

		for (auto &itm : ListOfCreatedActors)
		{
			itm->SetLifeSpan(0.5);
		}

		// Destroi o túnel.
		SetLifeSpan(0.5);
		bIsPendingKill = true;
	}
}

void ATunnelUnit::ShuffleLight(int OptShuffle)
{
	switch (OptShuffle)
	{
	case 0:
		PoitLight01->SetVisibility(FMath::RandBool());
		PoitLight01->SetLightColor(GetRandColor());
		PoitLight02->SetVisibility(FMath::RandBool());
		PoitLight02->SetLightColor(GetRandColor());
		PoitLight03->SetVisibility(FMath::RandBool());
		PoitLight03->SetLightColor(GetRandColor());
		PoitLight04->SetVisibility(FMath::RandBool());
		PoitLight04->SetLightColor(GetRandColor());
		PoitLight05->SetVisibility(FMath::RandBool());
		PoitLight05->SetLightColor(GetRandColor());
		break;
	default:
		break;
	case 1:
		int32 opt = FMath::RandRange(1, 5);
		switch (opt)
		{
		case 1:
			PoitLight01->SetVisibility(FMath::RandBool());
			PoitLight01->SetLightColor(GetRandColor());
			break;
		case 2:
			PoitLight02->SetVisibility(FMath::RandBool());
			PoitLight02->SetLightColor(GetRandColor());
			break;
		case 3:
			PoitLight03->SetVisibility(FMath::RandBool());
			PoitLight03->SetLightColor(GetRandColor());
			break;
		case 4:
			PoitLight04->SetVisibility(FMath::RandBool());
			PoitLight04->SetLightColor(GetRandColor());
			break;
		case 5:
			PoitLight05->SetVisibility(FMath::RandBool());
			PoitLight05->SetLightColor(GetRandColor());
			break;

		default:
			break;
		}
	}
}

void ATunnelUnit::GetRandomPointIn3DBoxSpace(FVector &RandomPoint, UBoxComponent *BoundingBox)
{
	RandomPoint = UKismetMathLibrary::RandomPointInBoundingBox(BoundingBox->Bounds.Origin, BoundingBox->Bounds.BoxExtent);
}