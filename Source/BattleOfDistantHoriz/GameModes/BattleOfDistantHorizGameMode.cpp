// Copyright Epic Games, Inc. All Rights Reserved.

#include "BattleOfDistantHorizGameMode.h"
#include "BattleOfDistantHoriz/Characters/BattleOfDistantHorizPawn.h"
#include "BattleOfDistantHoriz/Characters/SpaceShipPawn.h"
#include "BattleOfDistantHoriz/Helpers/UserWidgetHelper.h"

ABattleOfDistantHorizGameMode::ABattleOfDistantHorizGameMode()
{
	// set default pawn class to our flying pawn
	// DefaultPawnClass = ABattleOfDistantHorizPawn::StaticClass();
	DefaultPawnClass = ASpaceShipPawn::StaticClass();
}

void ABattleOfDistantHorizGameMode::InitGame(const FString &MapName, const FString &Options, FString &ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

void ABattleOfDistantHorizGameMode::StartPlay()
{
	Super::StartPlay();
	auto HelperWidget = NewObject<UUserWidgetHelper>(this);

	if (HelperWidget)
	{
		HelperWidget->SetPlayerHudWidget(EDisplayWidget::ShowWidget);
	}

	OnChangeDifficultyLevel.Broadcast(EDifficultyLevel::SuperEasy);

	GetWorld()->GetTimerManager().SetTimer(IncrementTimeDuringGameTimerHandle, this, &ABattleOfDistantHorizGameMode::IncrementTimeDuringGame, 1.0f, true, 0.0f);
}

void ABattleOfDistantHorizGameMode::StartToLeaveMap()
{
	Super::StartToLeaveMap();
	auto HelperWidget = NewObject<UUserWidgetHelper>(this);

	if (HelperWidget)
	{
		HelperWidget->SetPlayerHudWidget(EDisplayWidget::HideWidget);
	}
}

EDifficultyLevel ABattleOfDistantHorizGameMode::GetDifficulty(int val)
{
	if (val < 30)
	{
		CurrentDifficulty = EDifficultyLevel::SuperEasy;
	}
	else if (val < 60)
	{
		CurrentDifficulty = EDifficultyLevel::Easy;
	}
	else if (val < 120)
	{
		CurrentDifficulty = EDifficultyLevel::Normal;
	}
	else if (val < 180)
	{
		CurrentDifficulty = EDifficultyLevel::AboveNormal;
	}
	else if (val < 220)
	{
		CurrentDifficulty = EDifficultyLevel::Hign;
	}
	else if (val < 280)
	{
		CurrentDifficulty = EDifficultyLevel::AboveHign;
	}
	else if (val < 330)
	{
		CurrentDifficulty = EDifficultyLevel::Extreme;
	}

	return CurrentDifficulty;
}

void ABattleOfDistantHorizGameMode::IncrementTimeDuringGame()
{
	EDifficultyLevel TempDifficulty = CurrentDifficulty;

	CurrentDifficulty = GetDifficulty(TimeDuringGame++);

	UE_LOG(LogTemp, Warning, TEXT("%d"), TempDifficulty);

	if(TempDifficulty != CurrentDifficulty)
		OnChangeDifficultyLevel.Broadcast(CurrentDifficulty);

}
