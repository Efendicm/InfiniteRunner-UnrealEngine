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
    //Used to store the coins in game and save for relaunch
    UPROPERTY(VisibleAnywhere, Category = Basic)
        int32 PlayerCoins = 0;

    UMySaveGame();
};
