// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HomeWidget.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEOFDISTANTHORIZ_API UHomeWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UHomeWidget(const FObjectInitializer& ObjectInitializer);
	
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton *BtnJogar = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton *BtnSair = nullptr;

private:
	UFUNCTION()
	void OnBtnJogar();

	UFUNCTION()
	void OnBtnSair();

};
