// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleOfDistantHorizGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "BattleOfDistantHoriz/Helpers/UserWidgetHelper.h"
#include "BattleOfDistantHoriz/Widgets/CountDownWidget.h"

// UBattleOfDistantHorizGameInstance::UBattleOfDistantHorizGameInstance(const FObjectInitializer& ObjectInitializer)
// {

// }

void UBattleOfDistantHorizGameInstance::OpenLevel()
{
    UGameplayStatics::OpenLevel(GetWorld(), "/Game/Maps/GameMap01");
}

void UBattleOfDistantHorizGameInstance::ReloadGame()
{
    count_down = 3;
    GetWorld()->GetTimerManager().SetTimer(CountDown, this, &UBattleOfDistantHorizGameInstance::ExecuteCountDown, 1, true, 0);
}

void UBattleOfDistantHorizGameInstance::ExecuteCountDown()
{
    auto HelperWidget = NewObject<UUserWidgetHelper>(this);

    if (HelperWidget)
    {
        if (auto wcd = Cast<UCountDownWidget>(HelperWidget->GetCountDownWidget()))
        {
            wcd->SetCountDownText(FString::FromInt(count_down));
            count_down--;
        }
        else
        {
            HelperWidget->SetCountDownWidget(EDisplayWidget::ShowWidget);
            if (auto wcd2 = Cast<UCountDownWidget>(HelperWidget->GetCountDownWidget()))
            {
                wcd2->SetCountDownText(FString::FromInt(count_down));
                count_down--;
            }
        }

        if (count_down < 0)
        {
            GetWorld()->GetTimerManager().ClearTimer(CountDown);
            HelperWidget->SetCountDownWidget(EDisplayWidget::HideWidget);

            OpenLevel();
        }
    }
}
