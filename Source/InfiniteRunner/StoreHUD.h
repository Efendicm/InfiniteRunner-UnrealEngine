// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StoreHUD.generated.h"

/**
 * 
 */
UCLASS()
class INFINITERUNNER_API UStoreHUD : public UUserWidget
{
	GENERATED_BODY()
public:
	//Calls the MainMenuGameMode
	UPROPERTY(VisibleInstanceOnly)
		class AMainMenuGameMode* Menu;
	//Calls the GameInstance
	UPROPERTY(VisibleInstanceOnly)
		class UMyGameInstance* SavedData;
	UPROPERTY(VisibleInstanceOnly)
		class UMapPick* Maps;

	UPROPERTY()
		bool LavaBuying = false;
	UPROPERTY()
		bool WaterBuying = false;
	UPROPERTY()
		bool SpaceBuying = false;
	//Create The LavaMap Button
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* LavaMapBtn;
	//Create The WaterMap button
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* WaterMapBtn;
	//Create The SpaceMap button
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* SpaceMapBtn;
	//Create The Yes button
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* YesBtn;
	//Create The No button
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* NoBtn;
	//Create The Okay button
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* OkayBtn;
	//Create The Back button
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* BackBtn;
	//overlay screen
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UCanvasPanel* PurchaseScreen;
	//OverLay Screen
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UCanvasPanel* NotEnoughMoney;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* WaterText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* LavaText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* SpaceText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* WaterCost;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* LavaCost;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* SpaceCost;

	virtual void NativeConstruct() override;
	//Create the Function For MainMenu and restart 
	UFUNCTION()
		void OnLavaMapClick();

	UFUNCTION()
		void OnWaterMapClick();

	UFUNCTION()
		void OnSpaceMapClick();

	UFUNCTION()
		void OnBackClick();

	UFUNCTION()
		void OnYesClick();

	UFUNCTION()
		void OnNoClick();

	UFUNCTION()
		void OnOkayClick();
};