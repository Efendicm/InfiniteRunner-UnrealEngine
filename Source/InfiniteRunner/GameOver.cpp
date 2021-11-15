// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOver.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include <Runtime\Engine\Classes\Kismet\GameplayStatics.h>
#include <Runtime\Engine\Classes\Kismet\KismetMathLibrary.h>
#include <InfiniteRunner\EndlessRunnerGameModeBase.h>
#include "LavaLevelGameMode.h"
#include "SpaceGameMode.h"
#include "WaterGameMode.h"
#include "MyGameInstance.h"
#include <InfiniteRunner\MySaveGame.h>

void UGameOver::NativeConstruct()
{
	//Create the MainMenu Button to call the MainMenu Level
	if (MainMenuBtn)
	{
		MainMenuBtn->OnClicked.AddDynamic(this, &UGameOver::OnMainMenuClick);
	}
	//restart the game after Death
	if (RestartBtn)
	{
		RestartBtn->OnClicked.AddDynamic(this, &UGameOver::OnRestartClick);
	}
}
//Used to Display the amount of coins the Player has
void UGameOver::CoinAmount(AEndlessRunnerGameModeBase* RunGameMode)
{
	if (RunGameMode)
	{
		CoinTotal->SetText(FText::AsNumber(0));
		RunGameMode->OnCoinCountChanged.AddDynamic(this, &UGameOver::GetCoinTotal);
	}
}
void UGameOver::CoinAmountLava(ALavaLevelGameMode* LavaGameMode)
{
	if (LavaGameMode)
	{
		CoinTotal->SetText(FText::AsNumber(0));
		LavaGameMode->OnCoinCountChanged.AddDynamic(this, &UGameOver::GetCoinTotal);
	}
}
void UGameOver::CoinAmountSpace(ASpaceGameMode* SpaceGameMode)
{
	if (SpaceGameMode)
	{
		CoinTotal->SetText(FText::AsNumber(0));
		SpaceGameMode->OnCoinCountChanged.AddDynamic(this, &UGameOver::GetCoinTotal);
	}
}
void UGameOver::CoinAmountWater(AWaterGameMode* WaterGameMode)
{
	if (WaterGameMode)
	{
		CoinTotal->SetText(FText::AsNumber(0));
		WaterGameMode->OnCoinCountChanged.AddDynamic(this, &UGameOver::GetCoinTotal);
	}
}
//Used to call the total amount of coins in the run
void UGameOver::GetCoinTotal(const int32 Count)
{
	CoinTotal->SetText(FText::AsNumber(Count));
}
//make the Function for the mainMenu buttton
void UGameOver::OnMainMenuClick()
{
	UMyGameInstance* SavedData = Cast<UMyGameInstance>(GetGameInstance());
	RunGame = Cast<AEndlessRunnerGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	LavaGame = Cast<ALavaLevelGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	SpaceGame = Cast<ASpaceGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	WaterGame = Cast<AWaterGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (RunGame)
	{
		SavedData->CoinsSaved();
	}
	if (LavaGame)
	{
		SavedData->LavaCoinsSaved();
	}
	if (SpaceGame)
	{
		SavedData->SpaceCoinsSaved();
	}
	if (WaterGame)
	{
		SavedData->WaterCoinsSaved();
	}
	if (UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass())))
	{
		// Set data on the savegame object.
		SaveGameInstance->PlayerCoins = SavedData->TotalCoins;
		SaveGameInstance->LavaMapBought = SavedData->LavaBought;
		SaveGameInstance->WaterMapBought = SavedData->WaterBought;
		SaveGameInstance->SpaceMapBought = SavedData->SpaceBought;
		// Save the data immediately.
		if (UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("EndlessRunner"), 0))
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("GameSaved"));
		}
	}
	UWorld* World = GetWorld();
	if (World)
	{
		UGameplayStatics::OpenLevel(World, TEXT("MainMenu"));
	}
}
//Create Function for Restart Button
void UGameOver::OnRestartClick()
{
	UMyGameInstance* SavedData = Cast<UMyGameInstance>(GetGameInstance());
	RunGame = Cast<AEndlessRunnerGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	LavaGame = Cast<ALavaLevelGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	SpaceGame = Cast<ASpaceGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	WaterGame = Cast<AWaterGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (RunGame)
	{
		SavedData->CoinsSaved();
	}
	if (LavaGame)
	{
		SavedData->LavaCoinsSaved();
	}
	if (SpaceGame)
	{
		SavedData->SpaceCoinsSaved();
	}
	if (WaterGame)
	{
		SavedData->WaterCoinsSaved();
	}
	if (UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass())))
	{
		// Set data on the savegame object.
		SaveGameInstance->PlayerCoins = SavedData->TotalCoins;
		SaveGameInstance->LavaMapBought = SavedData->LavaBought;
		SaveGameInstance->WaterMapBought = SavedData->WaterBought;
		SaveGameInstance->SpaceMapBought = SavedData->SpaceBought;
		// Save the data immediately.
		if (UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("EndlessRunner"), 0))
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("GameSaved"));
		}
	}
	UWorld* World = GetWorld();
	if (World)
	{
		UKismetSystemLibrary::ExecuteConsoleCommand(World, TEXT("RestartLevel"));
	}
}

