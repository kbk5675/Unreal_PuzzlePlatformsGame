// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"

bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(BtnHost != nullptr)) return false;
	BtnHost->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

	if (!ensure(BtnJoin != nullptr)) return false;
	BtnJoin->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);

	if (!ensure(BtnCancle != nullptr)) return false;
	BtnCancle->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);

	if (!ensure(BtnConfirmJoin != nullptr)) return false;
	BtnConfirmJoin->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);

	if (!ensure(BtnExit != nullptr)) return false;
	BtnExit->OnClicked.AddDynamic(this, &UMainMenu::ExitServer);

	return true;
}

void UMainMenu::HostServer()
{
	if (MenuInterface != nullptr)
	{
		MenuInterface->Host();
	}
}

void UMainMenu::OpenJoinMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(JoinMenu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UMainMenu::OpenMainMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(MainMenu != nullptr)) return;
	MenuSwitcher->SetActiveWidget(MainMenu);
}

void UMainMenu::JoinServer()
{
	if (MenuInterface != nullptr)
	{
		if (!ensure(IPAddressField != nullptr)) return;
		const FString& Address = IPAddressField->GetText().ToString();
		MenuInterface->Join(Address);
	}
}

void UMainMenu::ExitServer()
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ConsoleCommand("quit");
}