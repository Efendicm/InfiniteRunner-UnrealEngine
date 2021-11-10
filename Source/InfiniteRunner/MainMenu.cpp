// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "MainMenuGameMode.h"
#include "Components/Button.h"
#include "EndlessRunnerGameModeBase.h"
#include "Components/TextBlock.h"
#include <Runtime\Engine\Classes\Kismet\GameplayStatics.h>
#include <Runtime\Engine\Classes\Kismet\KismetMathLibrary.h>
#include <InfiniteRunner\GameOver.h>

void UMainMenu::NativeConstruct()
{
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
}
//Create the Function for The Start button
void UMainMenu::OnStartClick()
{
	RemoveFromParent();
	UUserWidget* Widget = CreateWidget(GetWorld(), MapPick);
	if (Widget)
	{
		Widget->AddToViewport();
	}
}
//Create the function for the quit Button
void UMainMenu::OnQuitClick()
{
	UWorld* World = GetWorld();
	if (World)
	{
		UKismetSystemLibrary::ExecuteConsoleCommand(World, TEXT("quit"));
	}
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
