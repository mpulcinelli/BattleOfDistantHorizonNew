// Fill out your copyright notice in the Description page of Project Settings.
#include "SpaceShipPawn.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "BattleOfDistantHoriz/GameInstances/BattleOfDistantHorizGameInstance.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Particles/ParticleSystem.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Engine/StaticMesh.h"
#include "SpaceShipProjectile.h"
#include <cstdlib>
#include "BattleOfDistantHoriz/Helpers/UserWidgetHelper.h"
#include "BattleOfDistantHoriz/GameActors/TunnelUnit.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "Components/PointLightComponent.h"

// Sets default values
ASpaceShipPawn::ASpaceShipPawn()
{

	struct FConstructorStatics
	{

		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> SM_SPACESHIP_MESH;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> SM_LANDING_GEAR_BACK_MESH;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> SM_LANDING_GEAR_FRONT_MESH;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> SM_HARDPOINT1_MESH;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> SM_HARDPOINT2_MESH;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> SM_HARDPOINT3A_MESH;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> SM_HARDPOINT3B_MESH;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> SM_HARDPOINT4A_MESH;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> SM_HARDPOINT4B_MESH;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> SM_HARDPOINT5_MESH;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> SM_HARDPOINT6_MESH;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> SM_HARDPOINT7_MESH;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> SM_HARDPOINT8_MESH;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> SM_MISSILE1_MESH;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> SM_MISSILE2_MESH;
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> SM_SHIELD_MESH;
		ConstructorHelpers::FObjectFinderOptional<UParticleSystem> PS_COLLISION_EXPLODE;
		ConstructorHelpers::FObjectFinderOptional<USoundCue> CUE_CHARG_UP_SOUND;

		FConstructorStatics()
			: SM_SPACESHIP_MESH(TEXT("/Game/SciFi_Ship/Static_Meshes/Spaceship_alter")),
			  SM_LANDING_GEAR_BACK_MESH(TEXT("/Game/SciFi_Ship/Static_Meshes/Landing_Gear_Back")),
			  SM_LANDING_GEAR_FRONT_MESH(TEXT("/Game/SciFi_Ship/Static_Meshes/Landing_Gear_Front")),
			  SM_HARDPOINT1_MESH(TEXT("/Game/SciFi_Ship/Static_Meshes/Hardpoint_1")),
			  SM_HARDPOINT2_MESH(TEXT("/Game/SciFi_Ship/Static_Meshes/Hardpoint_1b")),
			  SM_HARDPOINT3A_MESH(TEXT("/Game/SciFi_Ship/Static_Meshes/Hardpoint_5b")),
			  SM_HARDPOINT3B_MESH(TEXT("/Game/SciFi_Ship/Static_Meshes/Hardpoint_5a")),
			  SM_HARDPOINT4A_MESH(TEXT("/Game/SciFi_Ship/Static_Meshes/Hardpoint_5b")),
			  SM_HARDPOINT4B_MESH(TEXT("/Game/SciFi_Ship/Static_Meshes/Hardpoint_5a")),
			  SM_HARDPOINT5_MESH(TEXT("/Game/SciFi_Ship/Static_Meshes/Hardpoint_3")),
			  SM_HARDPOINT6_MESH(TEXT("/Game/SciFi_Ship/Static_Meshes/Hardpoint_3")),
			  SM_HARDPOINT7_MESH(TEXT("/Game/SciFi_Ship/Static_Meshes/Hardpoint_2")),
			  SM_HARDPOINT8_MESH(TEXT("/Game/SciFi_Ship/Static_Meshes/Hardpoint_2")),
			  SM_MISSILE1_MESH(TEXT("/Game/SciFi_Ship/Static_Meshes/Missile_1")),
			  SM_MISSILE2_MESH(TEXT("/Game/SciFi_Ship/Static_Meshes/Missile_1")),
			  SM_SHIELD_MESH(TEXT("/Game/SciFi_Ship/Update1/Props/Spaceship_Shield")),
			  PS_COLLISION_EXPLODE(TEXT("/Game/MobileStarterContent/Particles/P_Explosion")),
			  CUE_CHARG_UP_SOUND(TEXT("/Game/Audio/sci-fi-charge-up_Cue"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
    AudioComponent->SetupAttachment(RootComponent);
    AudioComponent->SetAutoActivate(false);

    if(ConstructorStatics.CUE_CHARG_UP_SOUND.Get()!=nullptr){
        AudioComponent->SetSound(ConstructorStatics.CUE_CHARG_UP_SOUND.Get());
    }


	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (ConstructorStatics.PS_COLLISION_EXPLODE.Get() != nullptr)
	{
		CollisionExplodeParticle = ConstructorStatics.PS_COLLISION_EXPLODE.Get();
	}

	// Create static mesh component
	SpaceShip_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpaceShip_Mesh"));
	SpaceShip_Mesh->SetStaticMesh(ConstructorStatics.SM_SPACESHIP_MESH.Get());
	SpaceShip_Mesh->SetCollisionProfileName(FName("Pawn"));
	SpaceShip_Mesh->SetNotifyRigidBodyCollision(true);

	RootComponent = SpaceShip_Mesh;

	PoitLightTop = CreateDefaultSubobject<UPointLightComponent>(TEXT("PoitLightTop"));
	PoitLightTop->SetIntensity(100000.00);
	const FColor LC = FColor(205, 179, 117, 255);
	PoitLightTop->SetLightColor(FLinearColor::FromSRGBColor(LC));
	PoitLightTop->SetAttenuationRadius(16384.00);
	PoitLightTop->SetSourceRadius(17059.00);
	PoitLightTop->SetSourceLength(50);
	PoitLightTop->SetRelativeLocation(FVector(-894.000000, 0.000000, 725.000000));
	PoitLightTop->SetupAttachment(SpaceShip_Mesh);

	Hardpoint1_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hardpoint1_Mesh"));
	Hardpoint1_Mesh->SetStaticMesh(ConstructorStatics.SM_HARDPOINT1_MESH.Get());
	Hardpoint1_Mesh->SetupAttachment(SpaceShip_Mesh);
	Hardpoint1_Mesh->SetRelativeLocation(FVector(39.158077, -94.999969, -49.336540));
	Hardpoint1_Mesh->SetRelativeRotation(FRotator(0.000000, 90.000000, -0.000183));
	Hardpoint1_Mesh->SetRelativeScale3D(FVector(1.000000, 1.000000, 1.000000));

	ArrowGuid_2 = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowGuid_2"));
	ArrowGuid_2->SetupAttachment(Hardpoint1_Mesh);
	ArrowGuid_2->SetRelativeLocation(FVector(-38.000031, -136.000000, -9.000000));
	ArrowGuid_2->SetRelativeRotation(FRotator(0.000000, -90.000000, 0.000000));
	ArrowGuid_2->SetRelativeScale3D(FVector(1.000000, 1.000000, 1.000000));
	ArrowGuid_2->SetCollisionProfileName(FName("ArrowProfile"));

	ArrowCrossHairHandle = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowCrossHairHandle"));
	ArrowCrossHairHandle->SetupAttachment(SpaceShip_Mesh);
	ArrowCrossHairHandle->SetRelativeLocation(FVector(3000.000000, 0.000000, 0.000000));
	ArrowCrossHairHandle->SetRelativeRotation(FRotator(0.000000, 0.000000, 0.000000));
	ArrowCrossHairHandle->SetRelativeScale3D(FVector(1.000000, 1.000000, 1.000000));
	ArrowCrossHairHandle->SetSimulatePhysics(false);
	ArrowCrossHairHandle->SetCollisionProfileName(FName("ArrowProfile"));

	Hardpoint2_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hardpoint2_Mesh"));
	Hardpoint2_Mesh->SetStaticMesh(ConstructorStatics.SM_HARDPOINT2_MESH.Get());
	Hardpoint2_Mesh->SetupAttachment(SpaceShip_Mesh);
	Hardpoint2_Mesh->SetRelativeLocation(FVector(39.158077, 95.000031, -49.336540));
	Hardpoint2_Mesh->SetRelativeRotation(FRotator(0.000000, 90.000000, 0.000000));
	Hardpoint2_Mesh->SetRelativeScale3D(FVector(-1.000000, 1.000000, 1.000000));

	ArrowGuid_1 = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowGuid_1"));
	ArrowGuid_1->SetupAttachment(Hardpoint2_Mesh);
	ArrowGuid_1->SetRelativeLocation(FVector(-38.000000, -136.00000, -9.000000));
	ArrowGuid_1->SetRelativeRotation(FRotator(0.000000, 90.000000, 0.000000));
	ArrowGuid_1->SetRelativeScale3D(FVector(-1.000000, 1.000000, 1.000000));
	ArrowGuid_1->SetCollisionProfileName(FName("ArrowProfile"));

	Hardpoint3a_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hardpoint3a_Mesh"));
	Hardpoint3a_Mesh->SetStaticMesh(ConstructorStatics.SM_HARDPOINT3A_MESH.Get());
	Hardpoint3a_Mesh->SetupAttachment(SpaceShip_Mesh);
	Hardpoint3a_Mesh->SetRelativeLocation(FVector(250.000000, -116.000000, -107.000000));
	Hardpoint3a_Mesh->SetRelativeRotation(FRotator(0.000000, 90.000000, 0.00));

	Hardpoint3b_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hardpoint3b_Mesh"));
	Hardpoint3b_Mesh->SetStaticMesh(ConstructorStatics.SM_HARDPOINT3B_MESH.Get());
	Hardpoint3b_Mesh->SetupAttachment(Hardpoint3a_Mesh);
	Hardpoint3b_Mesh->SetRelativeLocation(FVector(0.000000, 0.000, 0.00));
	Hardpoint3b_Mesh->SetRelativeRotation(FRotator(0.000000, 0.000000, 0.00));

	ArrowGuid_3 = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowGuid_3"));
	ArrowGuid_3->SetupAttachment(Hardpoint3b_Mesh);
	ArrowGuid_3->SetRelativeLocation(FVector(0.000012, -57.999935, 2.000031));
	ArrowGuid_3->SetRelativeRotation(FRotator(0.000000, -90.000015, 0.000000));
	ArrowGuid_3->SetRelativeScale3D(FVector(1.000000, 1.000000, 1.000000));
	ArrowGuid_3->SetCollisionProfileName(FName("ArrowProfile"));

	Hardpoint4a_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hardpoint4a_Mesh"));
	Hardpoint4a_Mesh->SetStaticMesh(ConstructorStatics.SM_HARDPOINT4A_MESH.Get());
	Hardpoint4a_Mesh->SetupAttachment(SpaceShip_Mesh);
	Hardpoint4a_Mesh->SetRelativeLocation(FVector(250.000000, 116.000000, -107.000000));
	Hardpoint4a_Mesh->SetRelativeRotation(FRotator(0.000000, 90.000000, 0.000000));

	Hardpoint4b_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hardpoint4b_Mesh"));
	Hardpoint4b_Mesh->SetStaticMesh(ConstructorStatics.SM_HARDPOINT4B_MESH.Get());
	Hardpoint4b_Mesh->SetupAttachment(Hardpoint4a_Mesh);
	Hardpoint4b_Mesh->SetRelativeLocation(FVector(0.000000, 0.000, 0.00));
	Hardpoint4b_Mesh->SetRelativeRotation(FRotator(0.000000, 0.000000, 0.00));

	ArrowGuid_4 = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowGuid_4"));
	ArrowGuid_4->SetupAttachment(Hardpoint4b_Mesh);
	ArrowGuid_4->SetRelativeLocation(FVector(0.000000, -58.000214, 2.000038));
	ArrowGuid_4->SetRelativeRotation(FRotator(0.000000, -89.999985, 0.000000));
	ArrowGuid_4->SetRelativeScale3D(FVector(1.000000, 1.000000, 1.000000));
	ArrowGuid_4->SetCollisionProfileName(FName("ArrowProfile"));

	Hardpoint5_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hardpoint5_Mesh"));
	Hardpoint5_Mesh->SetStaticMesh(ConstructorStatics.SM_HARDPOINT5_MESH.Get());
	Hardpoint5_Mesh->SetupAttachment(SpaceShip_Mesh);
	Hardpoint5_Mesh->SetRelativeLocation(FVector(-647.000000, 470.000000, -90.000000));
	Hardpoint5_Mesh->SetRelativeRotation(FRotator(0.000000, 90.000000, -0.000183));

	ArrowGuid_5 = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowGuid_5"));
	ArrowGuid_5->SetupAttachment(Hardpoint5_Mesh);
	ArrowGuid_5->SetRelativeLocation(FVector(0.000183, -300.999298, 0.242222));
	ArrowGuid_5->SetRelativeRotation(FRotator(0.000000, -89.999992, 0.000000));
	ArrowGuid_5->SetRelativeScale3D(FVector(1.000000, 1.000000, 1.000000));
	ArrowGuid_5->SetCollisionProfileName(FName("ArrowProfile"));

	Hardpoint6_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hardpoint6_Mesh"));
	Hardpoint6_Mesh->SetStaticMesh(ConstructorStatics.SM_HARDPOINT6_MESH.Get());
	Hardpoint6_Mesh->SetupAttachment(SpaceShip_Mesh);
	Hardpoint6_Mesh->SetRelativeLocation(FVector(-647.002625, -470.000000, -90.000000));
	Hardpoint6_Mesh->SetRelativeRotation(FRotator(0.000000, 90.000000, -0.000183));
	Hardpoint6_Mesh->SetRelativeScale3D(FVector(-1.000000, 1.000000, 1.000000));

	ArrowGuid_6 = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowGuid_6"));
	ArrowGuid_6->SetupAttachment(Hardpoint6_Mesh);
	ArrowGuid_6->SetRelativeLocation(FVector(0.000122, -300.999878, 0.212144));
	ArrowGuid_6->SetRelativeRotation(FRotator(0.000000, 90.000000, 0.000000));
	ArrowGuid_6->SetRelativeScale3D(FVector(-1.000000, 1.000000, 1.000000));
	ArrowGuid_6->SetCollisionProfileName(FName("ArrowProfile"));

	Hardpoint7_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hardpoint7_Mesh"));
	Hardpoint7_Mesh->SetStaticMesh(ConstructorStatics.SM_HARDPOINT7_MESH.Get());
	Hardpoint7_Mesh->SetupAttachment(SpaceShip_Mesh);
	Hardpoint7_Mesh->SetRelativeLocation(FVector(-1065.996460, 760.194092, 16.261547));
	Hardpoint7_Mesh->SetRelativeRotation(FRotator(25.403126, -86.329445, 6.622577));

	Missile1_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Missile1_Mesh"));
	Missile1_Mesh->SetStaticMesh(ConstructorStatics.SM_MISSILE1_MESH.Get());
	Missile1_Mesh->SetupAttachment(Hardpoint7_Mesh);
	Missile1_Mesh->SetRelativeLocation(FVector(-0.011426, 17.765997, 9.942518));
	Missile1_Mesh->SetRelativeRotation(FRotator(43.199879, 0.000000, 0.000000));

	Hardpoint8_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hardpoint8_Mesh"));
	Hardpoint8_Mesh->SetStaticMesh(ConstructorStatics.SM_HARDPOINT8_MESH.Get());
	Hardpoint8_Mesh->SetupAttachment(SpaceShip_Mesh);
	Hardpoint8_Mesh->SetRelativeLocation(FVector(-1065.937622, -760.432739, 16.771074));
	Hardpoint8_Mesh->SetRelativeRotation(FRotator(-25.402170, -86.328018, 3.165193));

	Missile2_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Missile2_Mesh"));
	Missile2_Mesh->SetStaticMesh(ConstructorStatics.SM_MISSILE2_MESH.Get());
	Missile2_Mesh->SetupAttachment(Hardpoint8_Mesh);
	Missile2_Mesh->SetRelativeLocation(FVector(0.364495, 14.212234, 9.278972));
	Missile2_Mesh->SetRelativeRotation(FRotator(43.199879, 0.000000, 0.000000));

	Shield_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Shield_Mesh"));
	Shield_Mesh->SetStaticMesh(ConstructorStatics.SM_SHIELD_MESH.Get());
	Shield_Mesh->SetupAttachment(SpaceShip_Mesh);
	Shield_Mesh->SetRelativeLocation(FVector(0.00, 0.00, 0.00));
	Shield_Mesh->SetRelativeRotation(FRotator(0.000000, 90.000000, 0.000000));
	Shield_Mesh->SetVisibility(false);

	// Create a spring arm component
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm0"));
	SpringArm->SetupAttachment(SpaceShip_Mesh); // Attach SpringArm to RootComponent
	SpringArm->TargetArmLength = 1200.0f;		// The camera follows at this distance behind the character
	SpringArm->SocketOffset = FVector(0.f, 0.f, 0.f);
	SpringArm->bEnableCameraLag = false; // Do not allow camera to lag
	SpringArm->CameraLagSpeed = 15.f;
	SpringArm->SetRelativeRotation(FRotator(0.0, 0.0, 0.0));
	SpringArm->TargetOffset = FVector(-1240.000000, 0.000000, 730.000000);
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bInheritYaw = false;


	// Create camera component
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera0"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName); // Attach the camera
	Camera->bUsePawnControlRotation = true;								 // Don't rotate camera with controller

	// Set handling parameters
	Acceleration = 500.f;
	TurnSpeed = 50.f;
	MaxSpeed = 4000.f;
	MinSpeed = 500.f;
	CurrentForwardSpeed = 500.f;
	AmountLife = 100.0f;
	AmountFuel = 100.0f;
	// FuelBanks.Enqueue(AmountFuel);
}

void ASpaceShipPawn::ShowShield()
{
	UE_LOG(LogTemp, Warning, TEXT("ShowShield()"));
	if (!IsShieldVisible)
	{
		IsShieldVisible = true;
		Shield_Mesh->SetVisibility(IsShieldVisible);
	}
	else
	{
		IsShieldVisible = false;
		Shield_Mesh->SetVisibility(IsShieldVisible);
	}
}

void ASpaceShipPawn::AddFuel(float fuel)
{
	FuelBanks.Push(fuel);
	AudioComponent->Play();
}

// Called every frame
void ASpaceShipPawn::Tick(float DeltaSeconds)
{
	const FVector LocalMove = FVector(CurrentForwardSpeed * DeltaSeconds, 0.f, 0.f);

	// Move plan forwards (with sweep so we stop when we collide with things)
	AddActorLocalOffset(LocalMove, true);

	// Calculate change in rotation this frame
	FRotator DeltaRotation(0, 0, 0);
	DeltaRotation.Pitch = CurrentPitchSpeed * DeltaSeconds;
	DeltaRotation.Yaw = CurrentYawSpeed * DeltaSeconds;
	DeltaRotation.Roll = CurrentRollSpeed * DeltaSeconds;

	// Rotate plane
	AddActorLocalRotation(DeltaRotation, true);

	// FVector MyPosition = GetActorLocation();
	// GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Red, FString::Printf(TEXT("Some variable values: x: %f, y: %f, z: %f"), MyPosition.X, MyPosition.Y, MyPosition.Z));

	// Call any parent class Tick implementation
	Super::Tick(DeltaSeconds);
}

void ASpaceShipPawn::NotifyHit(class UPrimitiveComponent *MyComp, class AActor *Other, class UPrimitiveComponent *OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult &Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	if (bIsDead)
		return;

	FRotator CurrentRotation = GetActorRotation();

	SetActorRotation(FQuat::Slerp(CurrentRotation.Quaternion(), HitNormal.ToOrientationQuat(), 0.025f));

	if (UWorld *world = GetWorld())
	{
		UGameplayStatics::SpawnEmitterAtLocation(world, CollisionExplodeParticle, HitLocation, Hit.Normal.Rotation());
	}

	if (Other->GetClass() == ATunnelUnit::StaticClass())
	{
		DecrementLife(1);
	}
}

void ASpaceShipPawn::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(DecrementFuelTimerHandle, this, &ASpaceShipPawn::DecrementFuel, 2.0f, true, 2.0f);
}

void ASpaceShipPawn::NotifyActorBeginOverlap(AActor *OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (OtherActor->GetName().Contains("TurretEnemyProjectile"))
	{
		if (UWorld *world = GetWorld())
		{
			UGameplayStatics::SpawnEmitterAtLocation(world, CollisionExplodeParticle, OtherActor->GetActorLocation(), OtherActor->GetActorRotation());
		}
	}
}

// Called to bind functionality to input
void ASpaceShipPawn::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	// Check if PlayerInputComponent is valid (not NULL)
	check(PlayerInputComponent);

	// Bind our control axis' to callback functions
	PlayerInputComponent->BindAxis("Thrust", this, &ASpaceShipPawn::ThrustInput);
	PlayerInputComponent->BindAxis("MoveUp", this, &ASpaceShipPawn::MoveUpInput);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASpaceShipPawn::MoveRightInput);
	PlayerInputComponent->BindAction("Fire01", IE_Pressed, this, &ASpaceShipPawn::Fire01);
	PlayerInputComponent->BindAction("Fire02", IE_Pressed, this, &ASpaceShipPawn::Fire02);
	PlayerInputComponent->BindAction("Fire03", IE_Pressed, this, &ASpaceShipPawn::Fire03);
	PlayerInputComponent->BindAction("Fire04", IE_Pressed, this, &ASpaceShipPawn::Fire04);
	PlayerInputComponent->BindAction("Fire05", IE_Pressed, this, &ASpaceShipPawn::Fire05);
	PlayerInputComponent->BindAction("Fire06", IE_Pressed, this, &ASpaceShipPawn::Fire06);
	PlayerInputComponent->BindAction("ShowShield", IE_Pressed, this, &ASpaceShipPawn::ShowShield);
}

void ASpaceShipPawn::ThrustInput(float Val)
{
	// Is there any input?
	bool bHasInput = !FMath::IsNearlyEqual(Val, 0.f);
	// If input is not held down, reduce speed
	float CurrentAcc = bHasInput ? (Val * Acceleration) : (-0.5f * Acceleration);
	// Calculate new speed
	float NewForwardSpeed = CurrentForwardSpeed + (GetWorld()->GetDeltaSeconds() * CurrentAcc);
	// Clamp between MinSpeed and MaxSpeed
	CurrentForwardSpeed = FMath::Clamp(NewForwardSpeed, MinSpeed, MaxSpeed);
}

void ASpaceShipPawn::MoveUpInput(float Val)
{
	// Target pitch speed is based in input
	float TargetPitchSpeed = (Val * TurnSpeed * -1.f);

	// When steering, we decrease pitch slightly
	TargetPitchSpeed += (FMath::Abs(CurrentYawSpeed) * -0.2f);

	// Smoothly interpolate to target pitch speed
	CurrentPitchSpeed = FMath::FInterpTo(CurrentPitchSpeed, TargetPitchSpeed, GetWorld()->GetDeltaSeconds(), 2.f);
}

void ASpaceShipPawn::MoveRightInput(float Val)
{
	// Target yaw speed is based on input
	float TargetYawSpeed = (Val * TurnSpeed);

	// Smoothly interpolate to target yaw speed
	CurrentYawSpeed = FMath::FInterpTo(CurrentYawSpeed, TargetYawSpeed, GetWorld()->GetDeltaSeconds(), 2.f);

	// Is there any left/right input?
	const bool bIsTurning = FMath::Abs(Val) > 0.2f;

	// If turning, yaw value is used to influence roll
	// If not turning, roll to reverse current roll value.
	float TargetRollSpeed = bIsTurning ? (CurrentYawSpeed * 0.5f) : (GetActorRotation().Roll * -2.f);

	// Smoothly interpolate roll speed
	CurrentRollSpeed = FMath::FInterpTo(CurrentRollSpeed, TargetRollSpeed, GetWorld()->GetDeltaSeconds(), 2.f);
}

void ASpaceShipPawn::FireSelection(int FireType, FVector Loc, FRotator Rot)
{
	FActorSpawnParameters SpawnInfo;

	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	auto W = GetWorld();
	if (W != nullptr)
	{
		auto projectile = GetWorld()->SpawnActor<ASpaceShipProjectile>(Loc, Rot, SpawnInfo);
		if (projectile)
		{
			UE_LOG(LogTemp, Warning, TEXT("FireSelection"));
			projectile->ExecuteFire(FireType);
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

void ASpaceShipPawn::Fire01()
{
	if ((Fireshift_01 % 2) == 0)
	{
		FRotator Rot = ArrowGuid_1->GetComponentRotation();
		FVector Loc = ArrowGuid_1->GetComponentLocation();
		FireSelection(0, Loc, Rot);
		Fireshift_01 = 1;
	}
	else
	{
		FRotator Rot = ArrowGuid_2->GetComponentRotation();
		FVector Loc = ArrowGuid_2->GetComponentLocation();
		FireSelection(0, Loc, Rot);
		Fireshift_01 = 0;
	}
}

void ASpaceShipPawn::Fire02()
{
	if ((Fireshift_02 % 2) == 0)
	{
		FRotator Rot = ArrowGuid_3->GetComponentRotation();
		FVector Loc = ArrowGuid_3->GetComponentLocation();
		FireSelection(2, Loc, Rot);
		Fireshift_02 = 1;
	}
	else
	{
		FRotator Rot = ArrowGuid_4->GetComponentRotation();
		FVector Loc = ArrowGuid_4->GetComponentLocation();
		FireSelection(2, Loc, Rot);
		Fireshift_02 = 0;
	}
}

void ASpaceShipPawn::Fire03()
{
	if ((Fireshift_03 % 2) == 0)
	{
		FRotator Rot = ArrowGuid_5->GetComponentRotation();
		FVector Loc = ArrowGuid_5->GetComponentLocation();
		FireSelection(4, Loc, Rot);
		Fireshift_03 = 1;
	}
	else
	{
		FRotator Rot = ArrowGuid_6->GetComponentRotation();
		FVector Loc = ArrowGuid_6->GetComponentLocation();
		FireSelection(4, Loc, Rot);
		Fireshift_03 = 0;
	}
}

void ASpaceShipPawn::Fire04()
{
}

void ASpaceShipPawn::Fire05()
{
}

void ASpaceShipPawn::Fire06()
{
}

void ASpaceShipPawn::HideShipMesh()
{
	SpaceShip_Mesh->SetVisibility(false, true);

	auto GI = Cast<UBattleOfDistantHorizGameInstance>(GetGameInstance());
	if (GI)
	{
		GI->ReloadGame();
	}

	Destroy();
}

void ASpaceShipPawn::DecrementLife(float Value)
{
	AmountLife -= Value;

	if (AmountLife >= 0.0)
		OnPlayerDecrementLife.Broadcast(AmountLife);

	if (AmountLife < 0.0f)
	{
		bIsDead = true;
		AmountLife = 0.0f;
		ExplodeShip();
		OnPlayerDiedNow.Broadcast();
		OnPlayerDecrementLife.Broadcast(AmountLife);
	}
}

void ASpaceShipPawn::DecrementFuel()
{
	if (bIsDead)
		return;

	float FuelExpense = (CurrentForwardSpeed / MaxSpeed) * 10.0f;

	AmountFuel -= FuelExpense;

	OnPlayerDecrementFuelBank.Broadcast(FuelBanks.Num());

	if (AmountFuel > 0.0)
		OnPlayerDecrementFuel.Broadcast(AmountFuel);

	if (AmountFuel <= 0.0f)
	{
		if (FuelBanks.Num() <= 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("NO MORE BANKS"));
			bIsDead = true;
			AmountFuel = 0.0f;
			ExplodeShip();
			OnPlayerDiedNow.Broadcast();
			OnPlayerDecrementFuel.Broadcast(AmountFuel);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("USING EXISTANT BANK"));

			AmountFuel = FuelBanks.Pop(true);
			OnPlayerDecrementFuel.Broadcast(AmountFuel);
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("GASTO DE COMBUSTIVEL: %f"), FuelExpense);
	UE_LOG(LogTemp, Warning, TEXT("QUANTIDADE COMBUSTIVEL: %f"), AmountFuel);
}

void ASpaceShipPawn::ExplodeShip()
{
	auto W = GetWorld();
	if (W)
	{
		auto PC = W->GetFirstPlayerController();
		if (PC)
		{
			this->DisableInput(PC);
		}

		for (size_t i = 0; i < 20; i++)
		{
			FVector Origin = SpaceShip_Mesh->Bounds.Origin;
			FVector BoxExtent = SpaceShip_Mesh->Bounds.BoxExtent;
			FVector RandomPoint = UKismetMathLibrary::RandomPointInBoundingBox(Origin, BoxExtent);

			UGameplayStatics::SpawnEmitterAtLocation(W, CollisionExplodeParticle, RandomPoint);
		}

		HideShipMesh();
	}
}