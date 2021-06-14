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

	if (HelperWidget){
		HelperWidget->SetPlayerHudWidget(EDisplayWidget::ShowWidget);
	}
}

void ABattleOfDistantHorizGameMode::StartToLeaveMap()
{
	Super::StartToLeaveMap();
	auto HelperWidget = NewObject<UUserWidgetHelper>(this);

	if (HelperWidget){
		HelperWidget->SetPlayerHudWidget(EDisplayWidget::HideWidget);
	}

}
