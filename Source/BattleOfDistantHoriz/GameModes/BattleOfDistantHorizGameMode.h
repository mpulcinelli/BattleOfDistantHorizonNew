// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BattleOfDistantHorizGameMode.generated.h"

UENUM(BlueprintType)
enum class EDifficultyLevel : uint8
{
	SuperEasy UMETA(DisplayName = "Super Easy"),
	Easy UMETA(DisplayName = "Easy"),
	Normal UMETA(DisplayName = "Normal"),
	AboveNormal UMETA(DisplayName = "Above Normal"),
	Hign UMETA(DisplayName = "Hign"),
	AboveHign UMETA(DisplayName = "AboveHign"),
	Extreme UMETA(DisplayName = "Extreme"),
};

UCLASS(MinimalAPI)
class ABattleOfDistantHorizGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABattleOfDistantHorizGameMode();

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDifficultyLevelSignature, EDifficultyLevel, level);

	UPROPERTY(BlueprintAssignable)
	FDifficultyLevelSignature OnChangeDifficultyLevel;

	virtual void InitGame(const FString &MapName, const FString &Options, FString &ErrorMessage);
	virtual void StartPlay();
	virtual void StartToLeaveMap();
	EDifficultyLevel GetDifficulty(int val);

	FORCEINLINE EDifficultyLevel GetCurrentDifficulty() const { return CurrentDifficulty; }

private:
	FTimerHandle IncrementTimeDuringGameTimerHandle;

	EDifficultyLevel CurrentDifficulty;

	UFUNCTION()
	void IncrementTimeDuringGame();

	int TimeDuringGame = 0;
};
