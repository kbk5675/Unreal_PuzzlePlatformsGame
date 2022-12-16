// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "MenuInterface.h"
#include "GameoverMenu.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UGameoverMenu : public UMenuWidget
{
	GENERATED_BODY()

protected:
	virtual bool Initialize() override;

private:
	UFUNCTION()
	void BtnExitPressed();

	UPROPERTY(meta = (BindWidget))
	class UButton* BtnExit;
};
