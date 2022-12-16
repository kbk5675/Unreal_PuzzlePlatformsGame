// Fill out your copyright notice in the Description page of Project Settings.


#include "GameoverMenu.h"
#include "Components/Button.h"

bool UGameoverMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(BtnExit != nullptr)) return false;
	BtnExit->OnClicked.AddDynamic(this, &ThisClass::BtnExitPressed);

	return true;
}

void UGameoverMenu::BtnExitPressed()
{
	if (MenuInterface != nullptr)
	{
		OnLevelRemovedFromWorld(GetWorld()->GetLevel(0), GetWorld());
		MenuInterface->LoadMainMenu();
	}
}
