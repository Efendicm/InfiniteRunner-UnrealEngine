// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "EndlessRunnerGameModeBase.h"
#include "LavaLevelGameMode.h"
#include <InfiniteRunner\SpaceGameMode.h>
#include "WaterGameMode.h"
#include <InfiniteRunner\MySaveGame.h>


void UMyGameInstance::CoinsSaved()
{
	//Used to store current Games Coins from Run and add to total amount
	AEndlessRunnerGameModeBase* Coins = Cast<AEndlessRunnerGameModeBase>(GetWorld()->GetAuthGameMode());
	TotalCoins += Coins->TotalCoins;
}
void UMyGameInstance::LavaCoinsSaved()
{
	//Used to store current Games Coins from Run and add to total amount
	ALavaLevelGameMode* LavaCoins = Cast<ALavaLevelGameMode>(GetWorld()->GetAuthGameMode());
	TotalCoins += LavaCoins->TotalCoins;
}
void UMyGameInstance::SpaceCoinsSaved()
{
	//Used to store current Games Coins from Run and add to total amount
	ASpaceGameMode* SpaceCoins = Cast<ASpaceGameMode>(GetWorld()->GetAuthGameMode());
	TotalCoins += SpaceCoins->TotalCoins;
}
void UMyGameInstance::WaterCoinsSaved()
{
	//Used to store current Games Coins from Run and add to total amount
	AWaterGameMode* WaterCoins = Cast<AWaterGameMode>(GetWorld()->GetAuthGameMode());
	TotalCoins += WaterCoins->TotalCoins;
}
