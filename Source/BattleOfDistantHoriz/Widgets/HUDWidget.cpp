// Fill out your copyright notice in the Description page of Project Settings.

#include "HUDWidget.h"
#include "Kismet/GameplayStatics.h"
#include "BattleOfDistantHoriz/Characters/SpaceShipPawn.h"
#include "Components/ArrowComponent.h"
#include "Components/Image.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

void UHUDWidget::NativeTick(const FGeometry &MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    auto PC = GetWorld()->GetFirstPlayerController();
    if (PC)
    {
        auto PN = Cast<ASpaceShipPawn>(PC->GetPawn());
        if (PN)
        {
            FVector WPos = PN->ArrowCrossHairHandle->GetComponentLocation();
            FVector2D RetScreenPos;
            UGameplayStatics::ProjectWorldToScreen(PC, WPos, RetScreenPos);

            if (ImgCrossHair)
            {
                UCanvasPanelSlot *GridAsPanelSlot = Cast<UCanvasPanelSlot>(ImgCrossHair->Slot);
                GridAsPanelSlot->SetPosition(RetScreenPos);
            }
        }
    }
}

bool UHUDWidget::Initialize()
{
    Super::Initialize();

    auto PC = GetWorld()->GetFirstPlayerController();
    if (PC)
    {
        auto PN = Cast<ASpaceShipPawn>(PC->GetPawn());
        if (PN)
        {
            PN->OnPlayerDecrementLife.AddDynamic(this, &UHUDWidget::UpdateValorVida);
            PN->OnPlayerDecrementFuel.AddDynamic(this, &UHUDWidget::UpdateValorCombustivel);
            PN->OnPlayerDecrementFuelBank.AddDynamic(this, &UHUDWidget::UpdateValorBancoCombustivel);
        }
    }

    return true;
}

void UHUDWidget::UpdateValorVida(float valor)
{
    //TxtLife->SetText(FText::FromString(FString::SanitizeFloat(valor)));
    float percent = valor / 100.0f;
    PBarLife->SetPercent(percent);
}

void UHUDWidget::UpdateValorCombustivel(float valor)
{
    float percent = valor / 100.0f;
    PBarFuel->SetPercent(percent);
    UE_LOG(LogTemp, Warning, TEXT("COMBUSTIVEL TELA: %f"), percent);
}

void UHUDWidget::UpdateValorBancoCombustivel(int valor)
{
    TxtNumFuelBanks->SetText(FText::FromString(FString::FromInt(valor)));
}
