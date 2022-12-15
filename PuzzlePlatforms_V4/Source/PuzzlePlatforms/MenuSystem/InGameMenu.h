// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "MenuInterface.h"
#include "InGameMenu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UInGameMenu : public UMenuWidget
{
	GENERATED_BODY()

protected:
	virtual bool Initialize() override;

private:
	UFUNCTION()
		void CanclePressed();

	UFUNCTION()
		void QuitPressed();

	UPROPERTY(meta = (BindWidget))
	class UButton* BtnCancle;

	UPROPERTY(meta = (BindWidget))
	class UButton* BtnQuit;
};
