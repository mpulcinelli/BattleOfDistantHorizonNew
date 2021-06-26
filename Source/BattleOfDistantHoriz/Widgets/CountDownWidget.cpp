// Fill out your copyright notice in the Description page of Project Settings.


#include "CountDownWidget.h"
#include "Components/TextBlock.h"

UCountDownWidget::UCountDownWidget(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{

}

void UCountDownWidget::SetCountDownText(FString itemCount)
{
    if(TxtCountDown)
        TxtCountDown->SetText(FText::FromString(itemCount));
}
