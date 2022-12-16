// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameMenu.h"
#include "Components/Button.h"

bool UInGameMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(BtnCancle != nullptr)) return false;
	BtnCancle->OnClicked.AddDynamic(this, &ThisClass::CanclePressed);
	
	if (!ensure(BtnQuit != nullptr)) return false;
	BtnQuit->OnClicked.AddDynamic(this, &ThisClass::QuitPressed);

	return true;
}

void UInGameMenu::CanclePressed()
{
	OnLevelRemovedFromWorld(GetWorld()->GetLevel(0),GetWorld());
}

void UInGameMenu::QuitPressed()
{
	if (MenuInterface != nullptr)
	{
		OnLevelRemovedFromWorld(GetWorld()->GetLevel(0), GetWorld());
		MenuInterface->LoadMainMenu();
	}
}
