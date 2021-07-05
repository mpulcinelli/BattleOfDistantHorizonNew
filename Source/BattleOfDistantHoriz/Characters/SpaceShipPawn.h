// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SpaceShipPawn.generated.h"

UCLASS()
class BATTLEOFDISTANTHORIZ_API ASpaceShipPawn : public APawn
{
	GENERATED_BODY()

public:

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerDecrementLife, float, ponto);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerDecrementFuel, float, fuel);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerDecrementFuelBank, int, fuelBank);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerDiedNow);


	UPROPERTY(BlueprintAssignable)
	FPlayerDecrementLife OnPlayerDecrementLife;

	UPROPERTY(BlueprintAssignable)
	FPlayerDecrementFuel OnPlayerDecrementFuel;

	UPROPERTY(BlueprintAssignable)
	FPlayerDecrementFuelBank OnPlayerDecrementFuelBank;



	UPROPERTY(BlueprintAssignable)
	FPlayerDiedNow OnPlayerDiedNow;

	bool bIsDead=false;

	/** StaticMesh component that will be the visuals for our flying pawn */
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* SpaceShip_Mesh;

	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UPointLightComponent *PoitLightTop;



	/** StaticMesh component that will be the visuals for our flying pawn */
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Landing_Gear_Back_Mesh;

	/** StaticMesh component that will be the visuals for our flying pawn */
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Landing_Gear_Front_Mesh;

	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Hardpoint1_Mesh;

	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Hardpoint2_Mesh;

	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Hardpoint3a_Mesh;

	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Hardpoint3b_Mesh;

	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Hardpoint4a_Mesh;

	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Hardpoint4b_Mesh;

	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Hardpoint5_Mesh;

	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Hardpoint6_Mesh;

	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Hardpoint7_Mesh;

	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Hardpoint8_Mesh;

	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Missile1_Mesh;

	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Missile2_Mesh;

	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Shield_Mesh;

	UPROPERTY(Category = Audio, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UAudioComponent *AudioComponent;


	/** Spring arm that will offset the camera */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	/** Camera component that will be our viewpoint */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;


public:
	// Sets default values for this pawn's properties
	ASpaceShipPawn();
	// Begin AActor overrides
	virtual void Tick(float DeltaSeconds) override;
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	// End AActor overrides
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	class UArrowComponent* ArrowGuid_1;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	class UArrowComponent* ArrowGuid_2;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	class UArrowComponent* ArrowGuid_3;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	class UArrowComponent* ArrowGuid_4;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	class UArrowComponent* ArrowGuid_5;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	class UArrowComponent* ArrowGuid_6;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	class UArrowComponent* ArrowCrossHairHandle;

protected:

	// Begin APawn overrides
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override; // Allows binding actions/axes to functions
	// End APawn overrides

	/** Bound to the thrust axis */
	void ThrustInput(float Val);

	/** Bound to the vertical axis */
	void MoveUpInput(float Val);

	/** Bound to the horizontal axis */
	void MoveRightInput(float Val);

	UFUNCTION()
	void FireSelection(int FireType, FVector Loc, FRotator Rot);


	UFUNCTION()
	void Fire01();

	UFUNCTION()
	void Fire02();

	UFUNCTION()
	void Fire03();

	UFUNCTION()
	void Fire04();

	UFUNCTION()
	void Fire05();

	UFUNCTION()
	void Fire06();

	UFUNCTION()
	void ExplodeShip();

	UFUNCTION()
	void HideShipMesh();


private:

	FTimerHandle DecrementFuelTimerHandle;

	/** How quickly forward speed changes */
	UPROPERTY(Category=Plane, EditAnywhere)
	float Acceleration;

	/** How quickly forward speed changes */
	UPROPERTY(Category=Plane, EditAnywhere)
	float AmountLife;

	UPROPERTY(Category=Plane, EditAnywhere)
	float AmountFuel;


	/** How quickly pawn can steer */
	UPROPERTY(Category=Plane, EditAnywhere)
	float TurnSpeed;

	/** Max forward speed */
	UPROPERTY(Category = Pitch, EditAnywhere)
	float MaxSpeed;

	/** Min forward speed */
	UPROPERTY(Category=Yaw, EditAnywhere)
	float MinSpeed;

	/** Current forward speed */
	float CurrentForwardSpeed;

	/** Current yaw speed */
	float CurrentYawSpeed;

	/** Current pitch speed */
	float CurrentPitchSpeed;

	/** Current roll speed */
	float CurrentRollSpeed;


	int Fireshift_01 = 0;
	int Fireshift_02 = 0;
	int Fireshift_03 = 0;
	bool IsShieldVisible = false;

	class UParticleSystem* CollisionExplodeParticle;

	UFUNCTION()
	void DecrementFuel();

	TArray<float> FuelBanks;

public:

	UFUNCTION()
	void ShowShield();

	UFUNCTION()
	void AddFuel(float fuel);

	void DecrementLife(float Value);

	// /** Returns PlaneMesh subobject **/
	// FORCEINLINE class UStaticMeshComponent* GetPlaneMesh() const { return PlaneMesh; }
	/** Returns SpringArm subobject **/
	FORCEINLINE class USpringArmComponent* GetSpringArm() const { return SpringArm; }
	/** Returns Camera subobject **/
	FORCEINLINE class UCameraComponent* GetCamera() const { return Camera; }

};
