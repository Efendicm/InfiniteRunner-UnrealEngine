// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <InfiniteRunner\SpaceGameMode.h>
#include "GameHUDWidget.generated.h"



/**
 * 
 */
UCLASS()
class INFINITERUNNER_API UGameHUDWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	//Calls the pause menu widget
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UUserWidget> PauseMenuWidgetClass;
	//Distance Text
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* PlayerDistance;
	//Create the coin text block
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* CoinCount;
	//Create the powerUpIcon
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UImage* Invincible;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UImage* SuperFly;
	//pause button for Game
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* PauseBtn;
	//Create the function for pausing
	UFUNCTION()
		void OnPauseClick();

	virtual void NativeConstruct() override;
	//Calls to endless run for GamePaused
	UPROPERTY(VisibleInstanceOnly)
		class AEndlessRunnerGameModeBase* GamePaused;
	//Calls to EndlessRunner For the Power Up
	UPROPERTY(VisibleInstanceOnly)
		class AEndlessRunnerGameModeBase* Power;
	//Calls to the MainMenu For the CoinCount Changed
	UPROPERTY(VisibleInstanceOnly)
		class UMainMenu* CoinChanged;

	//Calls to the Runner to check if the power up was grabbed
	UPROPERTY(VisibleInstanceOnly)
		class ARunner* PowerUp;


	
public:

	UFUNCTION()
		void PowerUpToHUD();

	UFUNCTION()
		void Distance();
	//Sets booleans for Power Ups
	UPROPERTY(EditAnywhere)
		bool PowerUpOn = false;

	UPROPERTY(EditAnywhere)
		bool SuperFlyOn = false;


	UFUNCTION(BlueprintCallable)
		void InitializeHUD(AEndlessRunnerGameModeBase* RunGameMode);

	UFUNCTION(BlueprintCallable)
		void InitializeLavaHUD(ALavaLevelGameMode* LavaLevel);

	UFUNCTION(BlueprintCallable)
		void InitializeSpaceHUD(ASpaceGameMode* SpaceLevel);

	UFUNCTION(BlueprintCallable)
		void InitializeWaterHUD(AWaterGameMode* WaterLevel);


	UFUNCTION(BlueprintCallable)
		void SetCoinCount(int32 Count);

	void StoreWidgetAnimation();

	UWidgetAnimation* GetAnimationByName(FName AnimationName) const;

private:
	TMap<FName, UWidgetAnimation*> AnimationMap;

	UWidgetAnimation* SuperStrengthAnimation;

	UWidgetAnimation* SuperFlyingAnimation;
};
