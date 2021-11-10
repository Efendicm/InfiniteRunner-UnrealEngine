// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuGameMode.h"
#include "MainMenu.h"
#include "Components/TextBlock.h"
#include "EndlessRunnerGameModeBase.h"
#include <Runtime\Engine\Classes\Kismet\GameplayStatics.h>
#include <Runtime\Engine\Classes\Kismet\KismetMathLibrary.h>
#include <InfiniteRunner\EndlessRunnerGameModeBase.h>
#include "Blueprint/WidgetBlueprintLibrary.h"
#include <InfiniteRunner\GameOver.h>
#include <InfiniteRunner\MySaveGame.h>

class AEndlessRunnerGameModeBase;

void AMainMenuGameMode::BeginPlay()
{
	//Checks If the Game has a saved game and loads it
	if (UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass())))
	{
		UMyGameInstance* CoinsTotal = Cast<UMyGameInstance>(GetGameInstance());
		if (UGameplayStatics::DoesSaveGameExist("EndlessRunner", 0))
		{
			SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot("EndlessRunner", 0));
		}
		CoinsTotal->TotalCoins = SaveGameInstance->PlayerCoins;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("GameLoaded"));
	}
	//Adds the MainMenu HUD to game with coins if saved
	Menu = Cast<UMainMenu>(CreateWidget(GetWorld(), MainMenuWidgetClass));
	check(Menu);
	Menu->CoinAmount(this);
	Menu->AddToViewport();
}
