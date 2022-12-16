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
	void LoadInGameMenu();

	UFUNCTION(Exec, BlueprintCallable)
	void LoadGameoverMenu();

	UFUNCTION(Exec)
	void Host();

	UFUNCTION(Exec)
	void Join(const FString& Address);

	virtual void LoadMainMenu() override;

private:
	UPROPERTY()
	TSubclassOf<class UUserWidget> MainMenuClass;
	UPROPERTY()
	TSubclassOf<class UUserWidget> InGameMenuClass;
	UPROPERTY()
	TSubclassOf<class UUserWidget> GameoverMenuClass;

	class UMainMenu* MainMenu;
};
 