// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "MainMenuGameMode.h"
#include "Components/Button.h"
#include "MyGameInstance.h"
#include "EndlessRunnerGameModeBase.h"
#include "Components/TextBlock.h"
#include <Runtime\Engine\Classes\Kismet\GameplayStatics.h>
#include <Runtime\Engine\Classes\Kismet\KismetMathLibrary.h>
#include "StoreHUD.h"
#include "Components/CanvasPanel.h"
#include <InfiniteRunner\MySaveGame.h>
#include <InfiniteRunner\GameOver.h>

void UMainMenu::NativeConstruct()
{
	//Used to call Function in RunGameMode
	Menu = Cast<AMainMenuGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	//Create the Start button on MainMenu
	if (StartBtn)
	{
		StartBtn->OnClicked.AddDynamic(this, &UMainMenu::OnStartClick);
	}
	//used to create the Quit button on MainMenu
	if (QuitBtn)
	{
		QuitBtn->OnClicked.AddDynamic(this, &UMainMenu::OnQuitClick);
	}
	if (StoreBtn)
	{
		StoreBtn->OnClicked.AddDynamic(this, &UMainMenu::OnStoreClick);
	}
	if (OkayBtn)
	{

		OkayBtn->OnClicked.AddDynamic(this, &UMainMenu::OnOkayClick);
	}
	BoughtEverything->SetVisibility(ESlateVisibility::Collapsed);
}
//Create the Function for The Start button
void UMainMenu::OnStartClick()
{
	Menu->StartBtn();
}
//Create the function for the quit Button
void UMainMenu::OnQuitClick()
{
	//Saves the Coins From the Current Run
	UMyGameInstance* SavedData = Cast<UMyGameInstance>(GetGameInstance());
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
		UKismetSystemLibrary::ExecuteConsoleCommand(World, TEXT("quit"));
	}
}
void UMainMenu::OnStoreClick()
{
	//Checks to see if everything is bought
	UMyGameInstance* SavedData = Cast<UMyGameInstance>(GetGameInstance());
	if (SavedData->LavaBought && SavedData->SpaceBought && SavedData->WaterBought)
	{
		BoughtEverything->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		Menu->StorePicked();
	}
}
void UMainMenu::OnOkayClick()
{
	BoughtEverything->SetVisibility(ESlateVisibility::Collapsed);
}
//used to get the amount of Coins from the game played
void UMainMenu::CoinAmount(AMainMenuGameMode* MainMenu)
{
	if (MainMenu)
	{
		UMyGameInstance* Coins = Cast<UMyGameInstance>(GetGameInstance());
		CoinCountAmount(Coins->TotalCoins);
		
	}
}
//Sets the Amount of coins on the menu
void UMainMenu::CoinCountAmount(const int32 Count)
{
	CoinCount->SetText(FText::AsNumber(Count));
}
