
#include "PickUpBase.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"

// Sets default values
APickUpBase::APickUpBase(const FObjectInitializer &ObjectInitializer)
{
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> SM_PICK_UP;
		FConstructorStatics() : SM_PICK_UP(TEXT("/Game/Geometry/Meshes/PickUpMesh"))
		{
		}
	};

	static FConstructorStatics ConstructorStatics;

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PickUpMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickUpMesh"));

	RootComponent = PickUpMesh;

	if (ConstructorStatics.SM_PICK_UP.Get() != nullptr)
	{
		PickUpMesh->SetStaticMesh(ConstructorStatics.SM_PICK_UP.Get());
	}
}

// Called when the game starts or when spawned
void APickUpBase::BeginPlay()
{
	Super::BeginPlay();
}
