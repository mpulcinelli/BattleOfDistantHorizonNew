// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HomeGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEOFDISTANTHORIZ_API AHomeGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);
	virtual void StartToLeaveMap();
	virtual void StartPlay();
	
};
