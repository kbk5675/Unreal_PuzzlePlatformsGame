// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "PlatformTrigger.h"
#include "MenuSystem/MainMenu.h"
#include "MenuSystem/MenuWidget.h"
#include "MenuSystem/GameoverMenu.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer)
{
	// MainMenu
	ConstructorHelpers::FClassFinder<UUserWidget>MenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if (MenuBPClass.Succeeded())
	{
		MainMenuClass = MenuBPClass.Class;
	}

	// InGameMenu
	ConstructorHelpers::FClassFinder<UUserWidget>InGameMenuBPClass(TEXT("/Game/MenuSystem/WBP_INGameMenu"));
	if (InGameMenuBPClass.Succeeded())
	{
		InGameMenuClass = InGameMenuBPClass.Class;
	}
	
	// GameoverMenu
	ConstructorHelpers::FClassFinder<UUserWidget>GameoverMenuBPClass(TEXT("/Game/MenuSystem/WBP_Gameover"));
	if (GameoverMenuBPClass.Succeeded())
	{
		GameoverMenuClass = GameoverMenuBPClass.Class;
	}
}

void UPuzzlePlatformsGameInstance::Init()
{ 
	UE_LOG(LogTemp, Warning, TEXT("Found Class : %s"), *MainMenuClass->GetName());
}

void UPuzzlePlatformsGameInstance::LoadMenu()
{
	if (!ensure( MainMenuClass!= nullptr)) return;
	MainMenu = CreateWidget<UMainMenu>(this, MainMenuClass);
	if (!ensure(MainMenu != nullptr)) return;

	MainMenu->Setup();
	MainMenu->SetMenuInterface(this);
}

void UPuzzlePlatformsGameInstance::LoadInGameMenu()
{
	if (!ensure(InGameMenuClass != nullptr)) return;
	UMenuWidget* InGameMenu = CreateWidget<UMenuWidget>(this, InGameMenuClass);
	if (!ensure(InGameMenu != nullptr)) return;

	InGameMenu->Setup();
	InGameMenu->SetMenuInterface(this);
}

void UPuzzlePlatformsGameInstance::LoadGameoverMenu()
{
	if (!ensure(InGameMenuClass != nullptr)) return;
	UMenuWidget* GameoverMenu = CreateWidget<UMenuWidget>(this, GameoverMenuClass);
	if (!ensure(GameoverMenu != nullptr)) return;

	GameoverMenu->Setup();
	GameoverMenu->SetMenuInterface(this);
}

void UPuzzlePlatformsGameInstance::Host()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Hosting"));
	}
	
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;
	World->ServerTravel("/Game/Maps/MainMap?listen");
}

void UPuzzlePlatformsGameInstance::Join(const FString& Address)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));
	}

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure( PlayerController != nullptr)) return;

	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}

void UPuzzlePlatformsGameInstance::LoadMainMenu()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel("/Game/Maps/MainMenu?listen", ETravelType::TRAVEL_Absolute);
}