// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "GameOver.generated.h"

/**
 * 
 */
UCLASS()
class INFINITERUNNER_API UGameOver : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	//Calls the EndlessRunner class for the MainMenu
	UPROPERTY(VisibleInstanceOnly)
		class AEndlessRunnerGameModeBase* MainMenu;
	//Create the Coin Total Display
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* CoinTotal;
	//Create The MainMenu Button
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* MainMenuBtn;
	//Create The restart button
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* RestartBtn;

	virtual void NativeConstruct() override;
	//Create the Function For MainMenu and restart 
	UFUNCTION()
		void OnMainMenuClick();

	UFUNCTION()
		void OnRestartClick();

public:
	//Create The Function for the coin amount at game start and During the Run
	UFUNCTION(BlueprintCallable)
		void CoinAmount(AEndlessRunnerGameModeBase* RunGameMode);

	UFUNCTION(BlueprintCallable)
		void GetCoinTotal(int32 Count);
};
