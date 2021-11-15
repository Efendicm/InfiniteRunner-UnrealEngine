// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenu.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "EndlessRunnerGameModeBase.h"
#include "GameHUDWidget.h"
#include "LavaLevelGameMode.h"
#include "SpaceGameMode.h"
#include "WaterGameMode.h"
#include "MyGameInstance.h"
#include "Components/Button.h"
#include <InfiniteRunner\MySaveGame.h>
#include <Runtime\Engine\Classes\Kismet\GameplayStatics.h>

void UPauseMenu::NativeConstruct()
{
	//Used to call Function in RunGameMode
	RunGameMode = Cast<AEndlessRunnerGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	LavaGame = Cast<ALavaLevelGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	WaterGame = Cast<AWaterGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	SpaceGame = Cast<ASpaceGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (RunGameMode)
	{
		check(RunGameMode);
	}
	if (LavaGame)
	{
		check(LavaGame);
	}
	if (WaterGame)
	{
		check(WaterGame);
	}
	if (SpaceGame)
	{
		check(SpaceGame);
	}
	//Creates the Rusume Button
	if (ResumeBtn)
	{
		ResumeBtn->OnClicked.AddDynamic(this, &UPauseMenu::OnResumeClick);
	}
	//Create the Restart Button
	if (RestartBtn)
	{
		RestartBtn->OnClicked.AddDynamic(this, &UPauseMenu::OnRestartClick);
	}
	//Create the MainMenu Button
	if (MainMenuBtn)
	{
		MainMenuBtn->OnClicked.AddDynamic(this, &UPauseMenu::OnMainMenuClick);
	}
}
//Create the Function for Resume Button
void UPauseMenu::OnResumeClick()
{
	RemoveFromParent();
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	if (RunGameMode)
	{
		RunGameMode->GameUnPaused();
	}
	if (LavaGame)
	{
		LavaGame->GameUnPaused();
	}
	if (WaterGame)
	{
		WaterGame->GameUnPaused();
	}
	if (SpaceGame)
	{
		SpaceGame->GameUnPaused();
	}
}
//Create the Function for Restart Button
void UPauseMenu::OnRestartClick()
{
	//Saves the Current Coins from Run
	UMyGameInstance* SavedData = Cast<UMyGameInstance>(GetGameInstance());
	RunGameMode = Cast<AEndlessRunnerGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	LavaGame = Cast<ALavaLevelGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	SpaceGame = Cast<ASpaceGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	WaterGame = Cast<AWaterGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (RunGameMode)
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

//Create the Function for MainMenu Button
void UPauseMenu::OnMainMenuClick()
{
	//Saves the Coins From the Current Run
	UMyGameInstance* SavedData = Cast<UMyGameInstance>(GetGameInstance());
	RunGameMode = Cast<AEndlessRunnerGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	LavaGame = Cast<ALavaLevelGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	SpaceGame = Cast<ASpaceGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	WaterGame = Cast<AWaterGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (RunGameMode)
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


