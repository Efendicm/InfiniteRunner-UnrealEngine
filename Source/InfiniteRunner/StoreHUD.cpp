// Fill out your copyright notice in the Description page of Project Settings.


#include "StoreHUD.h"
#include "MapPick.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"
#include "MainMenuGameMode.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"
#include <Runtime\Engine\Classes\Kismet\GameplayStatics.h>
#include <Runtime\Engine\Classes\Kismet\KismetMathLibrary.h>
#include "MyGameInstance.h"
#include <InfiniteRunner\MySaveGame.h>

void UStoreHUD::NativeConstruct()
{
	 SavedData = Cast<UMyGameInstance>(GetGameInstance());
	//Used to call Function in RunGameMode
	Menu = Cast<AMainMenuGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	check(Menu);
	if (SavedData->LavaBought)
	{
		LavaMapBtn->SetVisibility(ESlateVisibility::Hidden);
		LavaText->SetVisibility(ESlateVisibility::Hidden);
		LavaCost->SetVisibility(ESlateVisibility::Hidden);
	}
	if (SavedData->WaterBought)
	{
		WaterMapBtn->SetVisibility(ESlateVisibility::Hidden);
		WaterText->SetVisibility(ESlateVisibility::Hidden);
		WaterCost->SetVisibility(ESlateVisibility::Hidden);
	}
	if (SavedData->SpaceBought)
	{
		SpaceMapBtn->SetVisibility(ESlateVisibility::Hidden);
		SpaceText->SetVisibility(ESlateVisibility::Hidden);
		SpaceCost->SetVisibility(ESlateVisibility::Hidden);
	}
	NotEnoughMoney->SetVisibility(ESlateVisibility::Collapsed);
	PurchaseScreen->SetVisibility(ESlateVisibility::Collapsed);
	//Create the MainMenu Button to call the MainMenu Level
	if (LavaMapBtn)
	{
		LavaMapBtn->OnClicked.AddDynamic(this, &UStoreHUD::OnLavaMapClick);
	}
	//restart the game after Death
	if (WaterMapBtn)
	{
		WaterMapBtn->OnClicked.AddDynamic(this, &UStoreHUD::OnWaterMapClick);
	}
	//Create the MainMenu Button to call the MainMenu Level
	if (SpaceMapBtn)
	{
		SpaceMapBtn->OnClicked.AddDynamic(this, &UStoreHUD::OnSpaceMapClick);
	}
	//restart the game after Death
	if (BackBtn)
	{

		BackBtn->OnClicked.AddDynamic(this, &UStoreHUD::OnBackClick);
	}

	if (YesBtn)
	{

		YesBtn->OnClicked.AddDynamic(this, &UStoreHUD::OnYesClick);
	}

	if (NoBtn)
	{

		NoBtn->OnClicked.AddDynamic(this, &UStoreHUD::OnNoClick);
	}

	if (OkayBtn)
	{

		OkayBtn->OnClicked.AddDynamic(this, &UStoreHUD::OnOkayClick);
	}
}

void UStoreHUD::OnLavaMapClick()
{
	if (SavedData->TotalCoins < 1000)
	{
		NotEnoughMoney->SetVisibility(ESlateVisibility::Visible);

	}
	if (SavedData->TotalCoins >= 1000)
	{
		LavaBuying = true;
		PurchaseScreen->SetVisibility(ESlateVisibility::Visible);
	}
}

void UStoreHUD::OnWaterMapClick()
{
	if (SavedData->TotalCoins < 500)
	{
		NotEnoughMoney->SetVisibility(ESlateVisibility::Visible);

	}
	if (SavedData->TotalCoins >= 500)
	{
		WaterBuying = true;
		PurchaseScreen->SetVisibility(ESlateVisibility::Visible);
	}
}

void UStoreHUD::OnSpaceMapClick()
{
	if (SavedData->TotalCoins < 1500)
	{
		NotEnoughMoney->SetVisibility(ESlateVisibility::Visible);

	}
	if (SavedData->TotalCoins >= 1500)
	{
		SpaceBuying = true;
		PurchaseScreen->SetVisibility(ESlateVisibility::Visible);
	}
}

void UStoreHUD::OnBackClick()
{
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
	Menu->StoreBackBtn();
}

void UStoreHUD::OnYesClick()
{
	if (LavaBuying)
	{
		LavaBuying = false;
		SavedData->LavaBought = true;
		SavedData->TotalCoins -= 1000;
		if (UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass())))
		{
			// Set data on the savegame object.
			SaveGameInstance->PlayerCoins = SavedData->TotalCoins;
			SaveGameInstance->LavaMapBought = SavedData->LavaBought;
			//SaveGameInstance->WaterMapBought = Menu->WaterBought;
			//SaveGameInstance->SpaceMapBought = Menu->SpaceBought;

			// Save the data immediately.
			if (UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("EndlessRunner"), 0))
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("GameSaved"));
			}
		}
		PurchaseScreen->SetVisibility(ESlateVisibility::Hidden);
		LavaMapBtn->SetVisibility(ESlateVisibility::Hidden);
		LavaText->SetVisibility(ESlateVisibility::Hidden);
		LavaCost->SetVisibility(ESlateVisibility::Hidden);
	}
	if (WaterBuying)
	{
		WaterBuying = false;
		SavedData->WaterBought = true;
		SavedData->TotalCoins -= 500;
		if (UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass())))
		{
			// Set data on the savegame object.
			SaveGameInstance->PlayerCoins = SavedData->TotalCoins;
			//SaveGameInstance->LavaMapBought = SavedData->LavaBought;
			SaveGameInstance->WaterMapBought = SavedData->WaterBought;
			//SaveGameInstance->SpaceMapBought = SavedData->SpaceBought;

			// Save the data immediately.
			if (UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("EndlessRunner"), 0))
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("GameSaved"));
			}
		}
		PurchaseScreen->SetVisibility(ESlateVisibility::Hidden);
		WaterMapBtn->SetVisibility(ESlateVisibility::Hidden);
		WaterText->SetVisibility(ESlateVisibility::Hidden);
		WaterCost->SetVisibility(ESlateVisibility::Hidden);
	}
	if (SpaceBuying)
	{
		SpaceBuying = false;
		SavedData->SpaceBought = true;
		SavedData->TotalCoins -= 1500;
		if (UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass())))
		{
			// Set data on the savegame object.
			SaveGameInstance->PlayerCoins = SavedData->TotalCoins;
			//SaveGameInstance->LavaMapBought = SavedData->LavaBought;
			//SaveGameInstance->WaterMapBought = SavedData->WaterBought;
			SaveGameInstance->SpaceMapBought = SavedData->SpaceBought;

			// Save the data immediately.
			if (UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("EndlessRunner"), 0))
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("GameSaved"));
			}
		}
		PurchaseScreen->SetVisibility(ESlateVisibility::Hidden);
		SpaceMapBtn->SetVisibility(ESlateVisibility::Hidden);
		SpaceText->SetVisibility(ESlateVisibility::Hidden);
		SpaceCost->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UStoreHUD::OnNoClick()
{
	PurchaseScreen->SetVisibility(ESlateVisibility::Hidden);
}

void UStoreHUD::OnOkayClick()
{
	NotEnoughMoney->SetVisibility(ESlateVisibility::Hidden);
}
