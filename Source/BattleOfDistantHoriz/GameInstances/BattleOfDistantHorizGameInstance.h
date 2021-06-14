// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BattleOfDistantHorizGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEOFDISTANTHORIZ_API UBattleOfDistantHorizGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	//UBattleOfDistantHorizGameInstance(const FObjectInitializer &ObjectInitializer);

	void OpenLevel();
	void ReloadGame();
	
private:
	FTimerHandle ReloadLevel;
	

};
