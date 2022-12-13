// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/Button.h"


bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(BtnHost != nullptr)) return false;
	BtnHost->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

	return true;
}

void UMainMenu::SetMenuInterface(IMenuInterface* MenuInterface)
{
	
}

void UMainMenu::Setup()
{
	if (this)
	{
		this->AddToViewport();
	}

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;
	
	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	FInputModeUIOnly InputModeData;
	this->bIsFocusable = true;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = true;
}

void UMainMenu::TearDown()
{
	this->RemoveFromViewport();

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	FInputModeGameOnly InputModeData;
	PlayerController->SetInputMode(InputModeData);

	PlayerController->bShowMouseCursor = false;
}

void UMainMenu::HostServer()
{
}