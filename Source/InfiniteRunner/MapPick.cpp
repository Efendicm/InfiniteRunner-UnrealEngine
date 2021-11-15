// Fill out your copyright notice in the Description page of Project Settings.


#include "MapPick.h"
#include "StoreHUD.h"
#include "MainMenuGameMode.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include <Runtime\Engine\Classes\Kismet\GameplayStatics.h>
#include "MainMenu.h"
#include "MyGameInstance.h"
#include <Runtime\Engine\Classes\Kismet\KismetMathLibrary.h>

void UMapPick::NativeConstruct()
{
	SavedData = Cast<UMyGameInstance>(GetGameInstance());
	//Used to call Function in RunGameMode
	MenuGameMode = Cast<AMainMenuGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	check(MenuGameMode);

	LavaBtn->SetVisibility(ESlateVisibility::Collapsed);
	LavaText->SetVisibility(ESlateVisibility::Collapsed);
	WaterBtn->SetVisibility(ESlateVisibility::Collapsed);
	WaterText->SetVisibility(ESlateVisibility::Collapsed);
	SpaceBtn->SetVisibility(ESlateVisibility::Collapsed);
	SpaceText->SetVisibility(ESlateVisibility::Collapsed);
	if (SavedData->LavaBought)
	{
		LavaBtn->SetVisibility(ESlateVisibility::Visible);
		LavaText->SetVisibility(ESlateVisibility::Visible);
	}
	if (SavedData->WaterBought)
	{
		WaterBtn->SetVisibility(ESlateVisibility::Visible);
		WaterText->SetVisibility(ESlateVisibility::Visible);
	}
	if (SavedData->SpaceBought)
	{
		SpaceBtn->SetVisibility(ESlateVisibility::Visible);
		SpaceText->SetVisibility(ESlateVisibility::Visible);
	}
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
	if (LavaBtn)
	{
		LavaBtn->OnClicked.AddDynamic(this, &UMapPick::OnLavaClick);
	}
	if (WaterBtn)
	{
		WaterBtn->OnClicked.AddDynamic(this, &UMapPick::OnWaterClick);
	}
	if (SpaceBtn)
	{
		SpaceBtn->OnClicked.AddDynamic(this, &UMapPick::OnSpaceClick);
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
	MenuGameMode->StartBackBtn();
}

void UMapPick::OnWaterClick()
{
	UWorld* World = GetWorld();
	if (World)
	{
		UGameplayStatics::OpenLevel(World, TEXT("WaterMap"));
	}
}

void UMapPick::OnLavaClick()
{
	UWorld* World = GetWorld();
	if (World)
	{
		UGameplayStatics::OpenLevel(World, TEXT("LavaMap"));
	}
}

void UMapPick::OnSpaceClick()
{
	UWorld* World = GetWorld();
	if (World)
	{
		UGameplayStatics::OpenLevel(World, TEXT("SpaceMap"));
	}
}

