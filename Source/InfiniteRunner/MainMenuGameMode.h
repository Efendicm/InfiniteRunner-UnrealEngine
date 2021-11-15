// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EndlessRunnerGameModeBase.h"
#include "MainMenuGameMode.generated.h"



/**
 * 
 */

UCLASS()
class INFINITERUNNER_API AMainMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()
	

public:
	//Used to check if coins were saved
	UPROPERTY(VisibleInstanceOnly)
		class UMyGameInstance* Game;
//Create the HUD
	UPROPERTY(EditAnywhere)
		class UMainMenu* Menu;
	//Create the HUD
	UPROPERTY(EditAnywhere, Category = "Config")
		TSubclassOf<UUserWidget> MainMenuWidgetClass;
	//Create the StoreHUD
	UPROPERTY(EditAnywhere, Category = "Config")
		TSubclassOf<UUserWidget> StoreHUDClass;
	//Used to call The GameHUDWidgetClass
	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
		class UStoreHUD* StoreHud;

	UPROPERTY(EditAnywhere, Category = "Config")
		TSubclassOf<UUserWidget> MapHUDClass;

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
		class UMapPick* MapHud;

	UFUNCTION()
		void StorePicked();
	UFUNCTION()
		void StoreBackBtn();
	UFUNCTION()
		void StartBackBtn();
	UFUNCTION()
		void StartBtn();

	virtual void BeginPlay() override;
};
