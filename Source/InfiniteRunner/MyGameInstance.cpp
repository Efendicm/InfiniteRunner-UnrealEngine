// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "EndlessRunnerGameModeBase.h"
#include <InfiniteRunner\MySaveGame.h>


void UMyGameInstance::CoinsSaved()
{
	//Used to store current Games Coins from Run and add to total amount
	AEndlessRunnerGameModeBase* Coins = Cast<AEndlessRunnerGameModeBase>(GetWorld()->GetAuthGameMode());
	TotalCoins += Coins->TotalCoins;
}
