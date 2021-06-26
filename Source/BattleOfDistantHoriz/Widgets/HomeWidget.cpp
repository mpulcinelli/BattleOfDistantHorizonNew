// Fill out your copyright notice in the Description page of Project Settings.

#include "HomeWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/SlateWrapperTypes.h"
#include "Components/EditableTextBox.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "BattleOfDistantHoriz/GameInstances/BattleOfDistantHorizGameInstance.h"

UHomeWidget::UHomeWidget(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
}

void UHomeWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (BtnJogar)
    {
        BtnJogar->OnClicked.AddDynamic(this, &UHomeWidget::OnBtnJogar);
    }

    if (BtnSair)
    {
        BtnSair->OnClicked.AddDynamic(this, &UHomeWidget::OnBtnSair);
    }

    this->bIsFocusable = true;
}

void UHomeWidget::OnBtnJogar()
{

    auto GI = Cast<UBattleOfDistantHorizGameInstance>(GetGameInstance());
    if(GI!=nullptr){
        GI->OpenLevel();
    }
}

void UHomeWidget::OnBtnSair()
{
    UE_LOG(LogTemp, Warning, TEXT("OnBtnSair"));
}