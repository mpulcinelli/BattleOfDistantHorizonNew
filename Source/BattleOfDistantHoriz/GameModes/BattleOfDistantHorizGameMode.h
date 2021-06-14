// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BattleOfDistantHorizGameMode.generated.h"

UCLASS(MinimalAPI)
class ABattleOfDistantHorizGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABattleOfDistantHorizGameMode();

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);
	virtual void StartPlay();
	virtual void StartToLeaveMap();

};



