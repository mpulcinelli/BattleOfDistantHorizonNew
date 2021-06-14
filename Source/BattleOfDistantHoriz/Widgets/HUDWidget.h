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
	

public:
	virtual void NativeTick(const FGeometry &MyGeometry, float InDeltaTime) override;
	virtual bool Initialize() override;

private:
	UFUNCTION()
	void UpdateValorVida(float valor);

	UFUNCTION()
	void UpdateValorCombustivel(float valor);

};
