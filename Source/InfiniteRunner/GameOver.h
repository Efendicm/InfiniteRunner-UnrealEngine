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
	//Calls to endlessRunnerGameMode
	UPROPERTY(VisibleInstanceOnly)
		class AEndlessRunnerGameModeBase* RunGame;
	//Calls to LavaLevelGameMode
	UPROPERTY(VisibleInstanceOnly)
		class ALavaLevelGameMode* LavaGame;
	//Calls to LavaLevelGameMode
	UPROPERTY(VisibleInstanceOnly)
		class ASpaceGameMode* SpaceGame;
	//Calls to LavaLevelGameMode
	UPROPERTY(VisibleInstanceOnly)
		class AWaterGameMode* WaterGame;
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
		void CoinAmountLava(ALavaLevelGameMode* LavaGameMode);
	UFUNCTION(BlueprintCallable)
		void CoinAmountSpace(ASpaceGameMode* SpaceGameMode);
	UFUNCTION(BlueprintCallable)
		void CoinAmountWater(AWaterGameMode* WaterGameMode);

	UFUNCTION(BlueprintCallable)
		void GetCoinTotal(int32 Count);
};
