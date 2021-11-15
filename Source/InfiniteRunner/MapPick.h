// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MapPick.generated.h"

/**
 * 
 */
UCLASS()
class INFINITERUNNER_API UMapPick : public UUserWidget
{
	GENERATED_BODY()
	

protected:
	//Calls to the MainMenu HUD
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TSubclassOf<class UUserWidget> MainMenu;
	//Calls the GameInstance
	UPROPERTY(VisibleInstanceOnly)
		class UMyGameInstance* SavedData;
	//Create the Day Button
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* DayBtn;
	//Create the Night Button
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* NightBtn;
	//Create the Water Button
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* WaterBtn;
	//Create the Lava Button
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* LavaBtn;
	//Create the Space Button
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* SpaceBtn;
	//Create the Back Button
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* BackBtn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* WaterText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* LavaText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* SpaceText;

	UPROPERTY(VisibleInstanceOnly)
		class UStoreHUD* Maps;

	virtual void NativeConstruct() override;
	//Create the function for the Buttons
	UFUNCTION()
		void OnDayClick();

	UFUNCTION()
		void OnNightClick();

	UFUNCTION()
		void OnBackClick();

	UFUNCTION()
		void OnWaterClick();

	UFUNCTION()
		void OnLavaClick();

	UFUNCTION()
		void OnSpaceClick();

public:
	//Used to call the MainMenuWidget
	UPROPERTY(EditAnywhere)
		class UMainMenu* Menu;
	//Used to call MainMenuGameMode
	UPROPERTY(EditAnywhere)
		class AMainMenuGameMode* MenuGameMode;

};
