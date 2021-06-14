// Fill out your copyright notice in the Description page of Project Settings.

#include "UserWidgetHelper.h"

#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "BattleOfDistantHoriz/Widgets/HomeWidget.h"
#include "BattleOfDistantHoriz/Widgets/HUDWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void UUserWidgetHelper::ShowEntrada()
{
    FSoftClassPath WBP_ENTRADA(TEXT("WidgetBlueprint'/Game/UI/WBP_ENTRADA.WBP_ENTRADA_C'"));

    UClass *WbpEntradaClass = WBP_ENTRADA.TryLoadClass<UHomeWidget>();
    if (!ensureAlwaysMsgf(WbpEntradaClass, TEXT("Problema com TryLoadClass<UHomeWidget>() em %s"), *FString(__func__)))
        return;

    UWorld *W = GetWorld();
    if (!ensureAlwaysMsgf(W, TEXT("Problema com GetWorld() em %s"), *FString(__func__)))
        return;

    APlayerController *PC = W->GetFirstPlayerController();
    if (!ensureAlwaysMsgf(PC, TEXT("Problema com GetFirstPlayerController() em %s"), *FString(__func__)))
        return;

    UUserWidget *EntradaWidget = CreateWidget<UUserWidget>(PC, WbpEntradaClass);
    if (!ensureAlwaysMsgf(EntradaWidget, TEXT("Problema com CreateWidget() em %s"), *FString(__func__)))
        return;

    EntradaWidget->AddToViewport();
    PC->bShowMouseCursor = true;

    UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PC, EntradaWidget, EMouseLockMode::DoNotLock);
}

void UUserWidgetHelper::HideEntrada()
{
    TArray<UUserWidget *> FoundWidgets;

    UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundWidgets, UHomeWidget::StaticClass());

    for (auto &&item : FoundWidgets)
    {
        item->RemoveFromViewport();
    }
}

void UUserWidgetHelper::ShowPlayerHud()
{
    FSoftClassPath WBP_HUD(TEXT("WidgetBlueprint'/Game/UI/WBP_HUD.WBP_HUD_C'"));

    UClass *WbpHudClass = WBP_HUD.TryLoadClass<UUserWidget>();
    if (!ensureAlwaysMsgf(WbpHudClass, TEXT("Problema com TryLoadClass<UHomeWidget>() em %s"), *FString(__func__)))
        return;

    UWorld *W = GetWorld();
    if (!ensureAlwaysMsgf(W, TEXT("Problema com GetWorld() em %s"), *FString(__func__)))
        return;

    APlayerController *PC = W->GetFirstPlayerController();
    if (!ensureAlwaysMsgf(PC, TEXT("Problema com GetFirstPlayerController() em %s"), *FString(__func__)))
        return;

    UUserWidget *HudWidget = CreateWidget<UUserWidget>(PC, WbpHudClass);
    if (!ensureAlwaysMsgf(HudWidget, TEXT("Problema com CreateWidget() em %s"), *FString(__func__)))
        return;

    HudWidget->AddToViewport();
    PC->bShowMouseCursor = false;

    UWidgetBlueprintLibrary::SetInputMode_GameOnly(PC);
}

void UUserWidgetHelper::HidePlayerHud()
{
    TArray<UUserWidget *> FoundWidgets;

    UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundWidgets, UHUDWidget::StaticClass());

    for (auto &&item : FoundWidgets)
        item->RemoveFromViewport();
}

void UUserWidgetHelper::SetEntradaWidget(EDisplayWidget DisplayOption)
{
    if (DisplayOption == EDisplayWidget::HideWidget)
        HideEntrada();
    else
        ShowEntrada();
}

void UUserWidgetHelper::SetPlayerHudWidget(EDisplayWidget DisplayOption)
{
    if (DisplayOption == EDisplayWidget::HideWidget)
        HidePlayerHud();
    else
        ShowPlayerHud();
}

UUserWidget *UUserWidgetHelper::GetPlayerHudWidget()
{
    TArray<UUserWidget *> FoundWidgets;

    UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundWidgets, UHUDWidget::StaticClass());

    for (auto &&item : FoundWidgets)
    {
        return item;
    }

    return nullptr;
}
