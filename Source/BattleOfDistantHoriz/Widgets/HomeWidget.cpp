// Fill out your copyright notice in the Description page of Project Settings.

#include "HomeWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/SlateWrapperTypes.h"
#include "Components/EditableTextBox.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

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
    UGameplayStatics::OpenLevel(GetWorld(), FName("/Game/Maps/GameMap"));
}

void UHomeWidget::OnBtnSair()
{
    UE_LOG(LogTemp, Warning, TEXT("OnBtnSair"));
}