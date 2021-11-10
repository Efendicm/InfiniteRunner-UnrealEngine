// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOver.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include <Runtime\Engine\Classes\Kismet\GameplayStatics.h>
#include <Runtime\Engine\Classes\Kismet\KismetMathLibrary.h>
#include <InfiniteRunner\EndlessRunnerGameModeBase.h>
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
//Used to call the total amount of coins in the run
void UGameOver::GetCoinTotal(const int32 Count)
{
	CoinTotal->SetText(FText::AsNumber(Count));
}
//make the Function for the mainMenu buttton
void UGameOver::OnMainMenuClick()
{
	UMyGameInstance* Coins = Cast<UMyGameInstance>(GetGameInstance());
	Coins->CoinsSaved();
	if (UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass())))
	{
		// Set data on the savegame object.
		SaveGameInstance->PlayerCoins = Coins->TotalCoins;

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
	UMyGameInstance* Coins = Cast<UMyGameInstance>(GetGameInstance());
	Coins->CoinsSaved();
	if (UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass())))
	{
		// Set data on the savegame object.
		SaveGameInstance->PlayerCoins = Coins->TotalCoins;

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

