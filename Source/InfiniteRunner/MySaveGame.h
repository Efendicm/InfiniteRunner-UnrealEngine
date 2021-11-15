// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MySaveGame.generated.h"

/**
 * 
 */
UCLASS()
class INFINITERUNNER_API UMySaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
    //Create a SaveSlot to save to game

    UPROPERTY(VisibleAnywhere, Category = Basic)
        FString SaveSlotName;

    UPROPERTY(VisibleAnywhere, Category = Basic)
        uint32 UserIndex;
    //Used to store the coins in game and save for relaunch
    UPROPERTY(VisibleAnywhere, Category = Basic)
        int32 PlayerCoins = 3000;
    //Used to store the Maps in game and save for relaunch
    UPROPERTY(VisibleAnywhere, Category = Basic)
        bool LavaMapBought;
    UPROPERTY(VisibleAnywhere, Category = Basic)
        bool WaterMapBought;
    UPROPERTY(VisibleAnywhere, Category = Basic)
        bool SpaceMapBought;

    UMySaveGame();
};
