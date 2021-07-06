// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

/**
 *
 */
UCLASS()
class BATTLEOFDISTANTHORIZ_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UImage *ImgCrossHair = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UProgressBar *PBarLife = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UProgressBar *PBarFuel = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock *TxtNumFuelBanks = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UProgressBar *PBarSpeed = nullptr;


public:
	virtual void NativeTick(const FGeometry &MyGeometry, float InDeltaTime) override;
	virtual bool Initialize() override;

private:
	UFUNCTION()
	void UpdateValorVelocidade(float valor, float min, float max);

	UFUNCTION()
	void UpdateValorVida(float valor);

	UFUNCTION()
	void UpdateValorCombustivel(float valor);

	UFUNCTION()
	void UpdateValorBancoCombustivel(int valor);


};
