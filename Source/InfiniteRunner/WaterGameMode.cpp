// Fill out your copyright notice in the Description page of Project Settings.


#include "WaterGameMode.h"
#include "Blueprint/UserWidget.h"
#include "GameHUDWidget.h"
#include "GameOver.h"
#include "WaterLevelSpawner.h"
#include "MainMenu.h"
#include "MyGameInstance.h"
#include <Runtime\Engine\Classes\Kismet\GameplayStatics.h>
#include <InfiniteRunner\Runner.h>


void AWaterGameMode::BeginPlay()
{

	//Create the Characters main hud calling to make the coins count
	GameHUD = Cast<UGameHUDWidget>(CreateWidget(GetWorld(), GameHUDClass));
	//Checks to see if the HUD is valid 
	check(GameHUD);
	//Calls to count the coins
	GameHUD->InitializeWaterHUD(this);
	//Adds Distance
	GameHUD->Distance();
	//Adds it to the game
	GameHUD->AddToViewport();
	//Create the GameOver HUD
	GameOverCoins = Cast<UGameOver>(CreateWidget(GetWorld(), GameOverScreenClass));
	//Checks to see if GameOver is valid
	check(GameOverCoins);
	//Calls the coins collected to the HUD
	GameOverCoins->CoinAmountWater(this);

	//Create The First 10 Floors fore endless spawning
	CreateInitialFloorTilesMiddle();
	CreateInitialFloorTilesLeft();
	CreateInitialFloorTilesRight();
	//Calls to see if the Super Speed Calls power up is called
	if (PowerUpOn)
	{
		GameHUD->PowerUpToHUD();

	}
}
//Create the default middle floors to have floors spawned already
void AWaterGameMode::CreateInitialFloorTilesMiddle()
{
	//Used to make the first floor have no Obsticles
	AddFloorTileMiddle(false);
	for (int i = 0; i < NumInitialFloorTilesMiddle; i++)
	{
		AddFloorTileMiddle(true);
	}
}
//Create the default Left floors to have floors spawned already
void AWaterGameMode::CreateInitialFloorTilesLeft()
{
	for (int i = 0; i < NumInitialFloorTilesLeft; i++)
	{
		AddFloorTileLeft(true);
	}
}
//Create the default Right floors to have floors spawned already
void AWaterGameMode::CreateInitialFloorTilesRight()
{
	for (int i = 0; i < NumInitialFloorTilesRight; i++)
	{
		AddFloorTileRight(true);
	}
}
//Adds Middle floors to the game based on the box collider on the given floor
AWaterLevelSpawner* AWaterGameMode::AddFloorTileMiddle(const bool MSpawnItems)
{
	UWorld* World = GetWorld();
	if (World)
	{
		AWaterLevelSpawner* Tile = World->SpawnActor<AWaterLevelSpawner>(FloorTileClassMiddle, NextSpawnPoint);

		if (Tile)
		{

			if (MSpawnItems)
			{
				Tile->SpawnItems();
			}

			NextSpawnPoint = Tile->GetAttachTransformMiddle();
		}
		return Tile;
	}
	return nullptr;
}
//Adds Right floors to the game based on the box collider on the given floor
AWaterLevelSpawner* AWaterGameMode::AddFloorTileRight(const bool RSpawnItems)
{
	UWorld* World = GetWorld();
	if (World)
	{
		AWaterLevelSpawner* Tile = World->SpawnActor<AWaterLevelSpawner>(FloorTileClassRight, NextSpawnPoint);

		if (Tile)
		{
			if (RSpawnItems)
			{
				Tile->SpawnItems();
			}


			NextSpawnPoint = Tile->GetAttachTransformRight();
		}
		return Tile;
	}
	return nullptr;
}
//Adds Left floors to the game based on the box collider on the given floor
AWaterLevelSpawner* AWaterGameMode::AddFloorTileLeft(const bool LSpawnItems)
{
	UWorld* World = GetWorld();
	if (World)
	{
		AWaterLevelSpawner* Tile = World->SpawnActor<AWaterLevelSpawner>(FloorTileClassLeft, NextSpawnPoint);

		if (Tile)
		{

			if (LSpawnItems)
			{
				Tile->SpawnItems();
			}

			NextSpawnPoint = Tile->GetAttachTransformLeft();
		}
		return Tile;
	}
	return nullptr;
}
//Used to count the coins collected
void AWaterGameMode::AddCoin()
{
	TotalCoins += 1;
	OnCoinCountChanged.Broadcast(TotalCoins);
}

//Adds the GameHUD Back to Port
void AWaterGameMode::GameUnPaused()
{
	GameHUD->AddToViewport();
}
//Pauses the Game and Removes the GameHUD
void AWaterGameMode::GamePaused()
{
	GameHUD->RemoveFromParent();
}
//Create The GameOver Screen
void AWaterGameMode::GameOver()
{
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	if (IsValid(GameOverScreenClass))
	{
		GameOverCoins->AddToViewport();

	}
}
//Used to Call the power up from Super Speed Class To Increase Speed and Destroy Object but also add the Icon to the HUD
void AWaterGameMode::PowerUp()
{
	if (PowerUpOn)
	{
		GameHUD->PowerUpOn = true;
		GameHUD->PowerUpToHUD();

	}
	if (!PowerUpOn)
	{
		GameHUD->PowerUpOn = false;
		GameHUD->PowerUpToHUD();

	}
	if (SuperFlying)
	{
		GameHUD->SuperFlyOn = true;
		GameHUD->PowerUpToHUD();

	}
	if (!SuperFlying)
	{
		GameHUD->SuperFlyOn = false;
		GameHUD->PowerUpToHUD();

	}

}
//Calls the PowerUp bool to be false and Makes the HUD icon Disappear
void AWaterGameMode::PowerUpOver()
{
	PowerUpOn = false;
	if (!PowerUpOn)
	{
		GameHUD->PowerUpToHUD();

	}

}