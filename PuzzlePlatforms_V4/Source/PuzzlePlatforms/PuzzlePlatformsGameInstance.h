// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuInterface.h"
#include "PuzzlePlatformsGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UPuzzlePlatformsGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()
	
public:
	UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer);
	virtual void Init() override;

	UFUNCTION(Exec, BlueprintCallable)
	void LoadMenu();
	
	UFUNCTION(Exec, BlueprintCallable)
	void InGameLoadMenu();

	UFUNCTION(Exec)
	void Host();

	UFUNCTION(Exec)
	void Join(const FString& Address);

	virtual void LoadMainMenu() override;

private:
	UPROPERTY()
	TSubclassOf<class UUserWidget> MainMenuClass;
	TSubclassOf<class UUserWidget> InGameMenuClass;

	class UMainMenu* MainMenu;
};
 