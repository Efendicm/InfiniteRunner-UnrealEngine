// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SpaceGameMode.generated.h"

class ASpaceLevelSpawner;
class UUserWidget;
//Create A muticast event for the Coin total
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSpaceCoinCountChanged, int32, CoinTotal);

UCLASS()
class INFINITERUNNER_API ASpaceGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	//Used to to store the current gaems Coins
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 TotalCoins = 0;
	//Called to see if power up is on or off
	UPROPERTY(EditAnywhere)
		bool PowerUpOn = false;
	//Called to see if SuperFly is on or off
	UPROPERTY(EditAnywhere)
		bool SuperFlying = false;
	//Create the HUD
	UPROPERTY(EditAnywhere, Category = "Config")
		TSubclassOf<UUserWidget> GameHUDClass;
	//Create the GameOver HUD
	UPROPERTY(EditAnywhere, Category = "Config")
		TSubclassOf<UUserWidget> GameOverScreenClass;
	//Create The Left Floors
	UPROPERTY(EditAnywhere, Category = "Config")
		TSubclassOf<ASpaceLevelSpawner> FloorTileClassLeft;
	//Create The Right Floors
	UPROPERTY(EditAnywhere, Category = "Config")
		TSubclassOf<ASpaceLevelSpawner> FloorTileClassRight;
	//Create the Middle Floors
	UPROPERTY(EditAnywhere, Category = "Config")
		TSubclassOf<ASpaceLevelSpawner> FloorTileClassMiddle;
	//Used to call The GameHUDWidgetClass
	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
		class UGameHUDWidget* GameHUD;
	//used to call GameOver class
	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
		class UGameOver* GameOverCoins;
	//Calls to the Game Instance class
	UPROPERTY(VisibleInstanceOnly)
		class UMyGameInstance* Game;
	//Calls to the Game Instance class
	UPROPERTY(VisibleInstanceOnly)
		class AEndlessRunnerGameModeBase* RunGameMode;
	//Create the default numver of floors to spawn on start for Left
	UPROPERTY(EditAnywhere, Category = "Config")
		int32 NumInitialFloorTilesLeft = 10;
	//Create the default numver of floors to spawn on start for Right
	UPROPERTY(EditAnywhere, Category = "Config")
		int32 NumInitialFloorTilesMiddle = 10;
	//Create the default numver of floors to spawn on start for Middle
	UPROPERTY(EditAnywhere, Category = "Config")
		int32 NumInitialFloorTilesRight = 10;
	//Calls the the arrow component to spwan next Island
	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
		FTransform NextSpawnPoint;
	//Calls the gameOver widget to stop game
	UFUNCTION(BlueprintCallable)
		void GameOver();
	//Create the Power Up
	UFUNCTION(BlueprintCallable)
		void PowerUp();
	//Calls when powerUp is Over
	UFUNCTION(BlueprintCallable)
		void PowerUpOver();
	//gets called from coin class to increase amount of coins
	UFUNCTION(BlueprintCallable)
		void AddCoin();
	//Create a pause for the game
	UFUNCTION(BlueprintCallable)
		void GamePaused();
	//Unpauses the game
	UFUNCTION(BlueprintCallable)
		void GameUnPaused();
	//Used to create Floors 
	UFUNCTION(BlueprintCallable)
		void CreateInitialFloorTilesLeft();
	void CreateInitialFloorTilesMiddle();
	void CreateInitialFloorTilesRight();

	//Called to Create a varible to hold the amount of coins the player has
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Delegates")
		FOnSpaceCoinCountChanged OnCoinCountChanged;
	//Adds the floors to the game
	UFUNCTION(BlueprintCallable)
	ASpaceLevelSpawner* AddFloorTileLeft(const bool LSpawnItems);
	ASpaceLevelSpawner* AddFloorTileMiddle(const bool MSpawnItems);
	ASpaceLevelSpawner* AddFloorTileRight(const bool RSpawnItems);

protected:
	//Timer for GameOver to Stop the game and show the Animatiion Death
	UPROPERTY()
		FTimerHandle RestartTimerHandle;

	virtual void BeginPlay() override;

};
