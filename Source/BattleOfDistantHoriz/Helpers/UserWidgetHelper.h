// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Blueprint/UserWidget.h"
#include "UserWidgetHelper.generated.h"


UENUM(BlueprintType)
enum class EDisplayWidget : uint8
{
	ShowWidget UMETA(DisplayName="ShowWidget"),
	HideWidget  UMETA(DisplayName="HideWidget")
};


/**
 * 
 */
UCLASS()
class BATTLEOFDISTANTHORIZ_API UUserWidgetHelper : public UObject
{
	GENERATED_BODY()

public:
	
	UFUNCTION()
	void SetEntradaWidget(EDisplayWidget DisplayOption);

	UFUNCTION()
	void SetPlayerHudWidget(EDisplayWidget DisplayOption);

	UFUNCTION()
	UUserWidget* GetPlayerHudWidget();

private:

	/**
	 * Entrada Widget
	*/
	UFUNCTION()
	void ShowEntrada();

	UFUNCTION()
	void HideEntrada();
	
	UFUNCTION()
	void ShowPlayerHud();

	UFUNCTION()
	void HidePlayerHud();

};
