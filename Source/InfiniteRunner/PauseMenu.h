// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenu.generated.h"


/**
 * 
 */
UCLASS()
class INFINITERUNNER_API UPauseMenu : public UUserWidget
{
	GENERATED_BODY()



protected:
	//Used to call MainMenuGameMode
	UPROPERTY(EditAnywhere)
		class AMainMenuGameMode* MenuGameMode;
	//Calls the RunGameMode
	UPROPERTY(VisibleInstanceOnly)
		class AEndlessRunnerGameModeBase* RunGameMode;
	//Calls to LavaLevelGameMode
	UPROPERTY(VisibleInstanceOnly)
		class ALavaLevelGameMode* LavaGame;
	//Calls to LavaLevelGameMode
	UPROPERTY(VisibleInstanceOnly)
		class ASpaceGameMode* SpaceGame;
	//Calls to LavaLevelGameMode
	UPROPERTY(VisibleInstanceOnly)
		class AWaterGameMode* WaterGame;
	//Used to Create the Animation for PowerUp
	UPROPERTY(VisibleInstanceOnly)
		class UGameHUDWidget* Animation;
	//Create the ResumeButton
		UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* ResumeBtn;
		//Create the RestartButton
		UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
			class UButton* RestartBtn;
		//Create the MainMenuButton
		UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
			class UButton* MainMenuBtn;

		virtual void NativeConstruct() override;
		//Create the Button Functions
		UFUNCTION()
			void OnResumeClick();

		UFUNCTION()
			void OnRestartClick();

		UFUNCTION()
			void OnMainMenuClick();
public:
	//Calls The GameHUDClass
	UPROPERTY(EditAnywhere, Category = "Config")
		TSubclassOf<UUserWidget> GameHUDClass;
};
