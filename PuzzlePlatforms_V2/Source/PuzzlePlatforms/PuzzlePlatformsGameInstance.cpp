// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "PlatformTrigger.h"
#include "MenuSystem/MainMenu.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget>MenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if (MenuBPClass.Succeeded())
	{
		MenuClass = MenuBPClass.Class;
	}
}

void UPuzzlePlatformsGameInstance::Init()
{ 
	UE_LOG(LogTemp, Warning, TEXT("Found Class : %s"), *MenuClass->GetName());
}

void UPuzzlePlatformsGameInstance::LoadMenu()
{
	if (!ensure( MenuClass!= nullptr)) return;
	Menu = CreateWidget<UMainMenu>(this, MenuClass);
	
	Menu->Setup();
	Menu->SetMenuInterface(this);
}

void UPuzzlePlatformsGameInstance::Host()
{
	if (Menu != nullptr)
	{
		Menu->TearDown();
	}

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Hosting"));
	}
	
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;
	World->ServerTravel("/Game/Maps/MainMap?listen");

	LoadMenu();
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