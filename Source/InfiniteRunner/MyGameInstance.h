// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"


UCLASS()
class INFINITERUNNER_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	//Checks to see if maps were Bought
	UPROPERTY()
		bool LavaBought = false;
	UPROPERTY()
		bool WaterBought = false;
	UPROPERTY()
		bool SpaceBought = false;
	//Used to call coin amount
	UPROPERTY(VisibleInstanceOnly)
		class AEndlessRunnerGameModeBase* CoinAmount;

	UPROPERTY(VisibleInstanceOnly)
		class ALavaLevelGameMode* LavaCoinAmount;

	UPROPERTY(VisibleInstanceOnly)
		class ASpaceGameMode* SpaceCoinAmount;

	UPROPERTY(VisibleInstanceOnly)
		class AWaterGameMode* WaterCoinAmount;
	//Used to store current run Coins so aren't deleted in map change
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 TotalCoins;
	//Creates Function for saving coins
	UFUNCTION()
		void CoinsSaved();

	UFUNCTION()
		void LavaCoinsSaved();

	UFUNCTION()
		void SpaceCoinsSaved();

	UFUNCTION()
		void WaterCoinsSaved();

};
