// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <InfiniteRunner\EndlessRunnerGameModeBase.h>
#include <InfiniteRunner\MyGameInstance.h>
#include "MainMenu.generated.h"

/**
 * 
 */



UCLASS()
class INFINITERUNNER_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
	

protected:
	//Gets the TotalCoins in game
	UPROPERTY(VisibleInstanceOnly)
		class UMyGameInstance* TotalCoins;

	//used to Create map selection Menu
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TSubclassOf<class UUserWidget> MapPick;


	virtual void NativeConstruct() override;
	//Create the Button Fuctions
	UFUNCTION()
		void OnStartClick();

	UFUNCTION()
		void OnQuitClick();

public:
	//Calls the MainMenuGameMode
	UPROPERTY(VisibleInstanceOnly)
		class AMainMenuGameMode* Menu;
	//Create the coins in the Menu
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* CoinCount;
	//Create the Start button
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* StartBtn;
	//Create The Quit Button
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* QuitBtn;
	//Call the Amount of coins in the Whole game
	UFUNCTION(BlueprintCallable)
		void CoinAmount(AMainMenuGameMode* MainMenu);

	//Set the Coin Amount
	UFUNCTION(BlueprintCallable)
		void CoinCountAmount(int32 Count);
};
