// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CountDownWidget.generated.h"

/**
 *
 */
UCLASS()
class BATTLEOFDISTANTHORIZ_API UCountDownWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UCountDownWidget(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock *TxtCountDown = nullptr;


	void SetCountDownText(FString itemCount);

};
