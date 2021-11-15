// Fill out your copyright notice in the Description page of Project Settings.


#include "LavaLevelGameMode.h"
#include "Blueprint/UserWidget.h"
#include "GameHUDWidget.h"
#include "GameOver.h"
#include "LavaLevelSpawner.h"
#include "MainMenu.h"
#include "MyGameInstance.h"
#include <Runtime\Engine\Classes\Kismet\GameplayStatics.h>
#include <InfiniteRunner\Runner.h>


void ALavaLevelGameMode::BeginPlay()
{

	//Create the Characters main hud calling to make the coins count
	GameHUD = Cast<UGameHUDWidget>(CreateWidget(GetWorld(), GameHUDClass));
	//Checks to see if the HUD is valid 
	check(GameHUD);
	//Calls to count the coins
	GameHUD->InitializeLavaHUD(this);
	//Adds Distance
	GameHUD->Distance();
	//Adds it to the game
	GameHUD->AddToViewport();
	//Create the GameOver HUD
	GameOverCoins = Cast<UGameOver>(CreateWidget(GetWorld(), GameOverScreenClass));
	//Checks to see if GameOver is valid
	check(GameOverCoins);
	//Calls the coins collected to the HUD
	GameOverCoins->CoinAmountLava(this);

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
void ALavaLevelGameMode::CreateInitialFloorTilesMiddle()
{
	//Used to make the first floor have no Obsticles
	AddFloorTileMiddle(false);
	for (int i = 0; i < NumInitialFloorTilesMiddle; i++)
	{
		AddFloorTileMiddle(true);
	}
}
//Create the default Left floors to have floors spawned already
void ALavaLevelGameMode::CreateInitialFloorTilesLeft()
{
	for (int i = 0; i < NumInitialFloorTilesLeft; i++)
	{
		AddFloorTileLeft(true);
	}
}
//Create the default Right floors to have floors spawned already
void ALavaLevelGameMode::CreateInitialFloorTilesRight()
{
	for (int i = 0; i < NumInitialFloorTilesRight; i++)
	{
		AddFloorTileRight(true);
	}
}
//Adds Middle floors to the game based on the box collider on the given floor
ALavaLevelSpawner* ALavaLevelGameMode::AddFloorTileMiddle(const bool MSpawnItems)
{
	UWorld* World = GetWorld();
	if (World)
	{
		ALavaLevelSpawner* Tile = World->SpawnActor<ALavaLevelSpawner>(FloorTileClassMiddle, NextSpawnPoint);

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
ALavaLevelSpawner* ALavaLevelGameMode::AddFloorTileRight(const bool RSpawnItems)
{
	UWorld* World = GetWorld();
	if (World)
	{
		ALavaLevelSpawner* Tile = World->SpawnActor<ALavaLevelSpawner>(FloorTileClassRight, NextSpawnPoint);

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
ALavaLevelSpawner* ALavaLevelGameMode::AddFloorTileLeft(const bool LSpawnItems)
{
	UWorld* World = GetWorld();
	if (World)
	{
		ALavaLevelSpawner* Tile = World->SpawnActor<ALavaLevelSpawner>(FloorTileClassLeft, NextSpawnPoint);

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
void ALavaLevelGameMode::AddCoin()
{
	TotalCoins += 1;
	OnCoinCountChanged.Broadcast(TotalCoins);
}

//Adds the GameHUD Back to Port
void ALavaLevelGameMode::GameUnPaused()
{
	GameHUD->AddToViewport();
}
//Pauses the Game and Removes the GameHUD
void ALavaLevelGameMode::GamePaused()
{
	GameHUD->RemoveFromParent();
}
//Create The GameOver Screen
void ALavaLevelGameMode::GameOver()
{
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	if (IsValid(GameOverScreenClass))
	{
		GameOverCoins->AddToViewport();

	}
}
//Used to Call the power up from Super Speed Class To Increase Speed and Destroy Object but also add the Icon to the HUD
void ALavaLevelGameMode::PowerUp()
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
void ALavaLevelGameMode::PowerUpOver()
{
	PowerUpOn = false;
	if (!PowerUpOn)
	{
		GameHUD->PowerUpToHUD();

	}

}
