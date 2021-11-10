// Fill out your copyright notice in the Description page of Project Settings.


#include "MapPick.h"
#include "MainMenuGameMode.h"
#include "Components/Button.h"
#include <Runtime\Engine\Classes\Kismet\GameplayStatics.h>
#include "MainMenu.h"
#include <Runtime\Engine\Classes\Kismet\KismetMathLibrary.h>

void UMapPick::NativeConstruct()
{
	//Create the Day Map button
	if (DayBtn)
	{
		DayBtn->OnClicked.AddDynamic(this, &UMapPick::OnDayClick);
	}
	//Create the Night Map button
	if (NightBtn)
	{
		NightBtn->OnClicked.AddDynamic(this, &UMapPick::OnNightClick);
	}
	//Create the back button
	if (BackBtn)
	{
		BackBtn->OnClicked.AddDynamic(this, &UMapPick::OnBackClick);
	}

}
//Function used to load day map
void UMapPick::OnDayClick()
{
	UWorld* World = GetWorld();
	if (World)
	{
		UGameplayStatics::OpenLevel(World, TEXT("SkyRunnerDay"));
	}
}
//Function used to call night map
void UMapPick::OnNightClick()
{
	UWorld* World = GetWorld();
	if (World)
	{
		UGameplayStatics::OpenLevel(World, TEXT("SkyRunnerNight"));
	}
}
//Function used to go back to MainMenu
void UMapPick::OnBackClick()
{
	RemoveFromParent();
	Menu = Cast<UMainMenu>(CreateWidget(GetWorld(), MainMenu));
	check(Menu);
	UMyGameInstance* Coins = Cast<UMyGameInstance>(GetGameInstance());
	Menu->CoinCountAmount(Coins->TotalCoins);
	Menu->AddToViewport();
}

