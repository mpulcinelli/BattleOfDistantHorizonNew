// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleOfDistantHorizGameInstance.h"
#include "Kismet/GameplayStatics.h"

// UBattleOfDistantHorizGameInstance::UBattleOfDistantHorizGameInstance(const FObjectInitializer& ObjectInitializer)
// {	

// }

void UBattleOfDistantHorizGameInstance::OpenLevel() 
{
    UE_LOG(LogTemp, Warning, TEXT("Abrindo Nivel"));
    UGameplayStatics::OpenLevel(GetWorld(), "/Game/Maps/GameMap");
}
void UBattleOfDistantHorizGameInstance::ReloadGame()
{

    GetWorld()->GetTimerManager().SetTimer(ReloadLevel, this, &UBattleOfDistantHorizGameInstance::OpenLevel, 3, false);    
    UE_LOG(LogTemp, Warning, TEXT("Recarregando Nivel"));    
}
