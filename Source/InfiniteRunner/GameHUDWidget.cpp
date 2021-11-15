// Fill out your copyright notice in the Description page of Project Settings.

#include "GameHUDWidget.h"

#include "GameOver.h"
#include "EndlessRunnerGameModeBase.h"
#include <InfiniteRunner\SpaceGameMode.h>
#include "WaterGameMode.h"
#include "LavaLevelGameMode.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Animation/WidgetAnimation.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/SlateWrapperTypes.h"
#include "MyGameInstance.h"
#include <Runtime\Engine\Classes\Kismet\GameplayStatics.h>
#include <InfiniteRunner\Runner.h>


void UGameHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//Store a list of animations to be called when ever
	StoreWidgetAnimation();
	//Create the Super Speed and Super Fly animation Icon
	SuperStrengthAnimation = GetAnimationByName(TEXT("SuperStrength"));
	SuperFlyingAnimation = GetAnimationByName(TEXT("SuperFlying"));
	//hides  Super Speed and Super Fly when the game Begins
	Invincible->SetVisibility(ESlateVisibility::Collapsed);
	SuperFly->SetVisibility(ESlateVisibility::Collapsed);
	//Create the Pause Button to pause game
	if (PauseBtn)
	{
		PauseBtn->OnClicked.AddDynamic(this, &UGameHUDWidget::OnPauseClick);
	}
	UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(UGameplayStatics::GetPlayerController(GetWorld(), 0), this);
}

//Create the default amount of coins when RungameMode is called
void UGameHUDWidget::InitializeHUD(AEndlessRunnerGameModeBase* RunGameMode)
{
	//Checks to see if its RunGameMode
	if (RunGameMode)
	{
		UMyGameInstance* Coins = Cast<UMyGameInstance>(GetGameInstance());
		CoinCount->SetText(FText::AsNumber(0));

		RunGameMode->OnCoinCountChanged.AddDynamic(this, &UGameHUDWidget::SetCoinCount);
	}
}
void UGameHUDWidget::InitializeLavaHUD(ALavaLevelGameMode* LavaLevel)
{
	if (LavaLevel)
	{
		UMyGameInstance* Coins = Cast<UMyGameInstance>(GetGameInstance());
		CoinCount->SetText(FText::AsNumber(0));

		LavaLevel->OnCoinCountChanged.AddDynamic(this, &UGameHUDWidget::SetCoinCount);
	}
}
void UGameHUDWidget::InitializeWaterHUD(AWaterGameMode* WaterLevel)
{
	if (WaterLevel)
	{
		UMyGameInstance* Coins = Cast<UMyGameInstance>(GetGameInstance());
		CoinCount->SetText(FText::AsNumber(0));

		WaterLevel->OnCoinCountChanged.AddDynamic(this, &UGameHUDWidget::SetCoinCount);
	}
}
void UGameHUDWidget::InitializeSpaceHUD(ASpaceGameMode* SpaceLevel)
{
	if (SpaceLevel)
	{
		UMyGameInstance* Coins = Cast<UMyGameInstance>(GetGameInstance());
		CoinCount->SetText(FText::AsNumber(0));

		SpaceLevel->OnCoinCountChanged.AddDynamic(this, &UGameHUDWidget::SetCoinCount);
	}
}
//Set the coin count as the store varible while playing
void UGameHUDWidget::SetCoinCount(const int32 Count)
{
	CoinCount->SetText(FText::AsNumber(Count));
}
//used to Create the pause button
void UGameHUDWidget::OnPauseClick()
{
	RemoveFromParent();
	if (UGameplayStatics::SetGamePaused(GetWorld(), true))
	{

		UUserWidget* Widget = CreateWidget(GetWorld(), PauseMenuWidgetClass);

		if (Widget)
		{
			Widget->AddToViewport();
		}
	}
}
//Create the PowerUp Icon
void UGameHUDWidget::PowerUpToHUD()
{
	if (PowerUpOn)
	{
		Invincible->SetVisibility(ESlateVisibility::Visible);
		if (SuperStrengthAnimation)
		{
			PlayAnimation(SuperStrengthAnimation, 0.f, 1, EUMGSequencePlayMode::Forward, 1.f);
		}
		
	}
	if (!PowerUpOn)
	{
		Invincible->SetVisibility(ESlateVisibility::Hidden);
	}
	if (SuperFlyOn)
	{
		SuperFly->SetVisibility(ESlateVisibility::Visible);
		if (SuperFlyingAnimation)
		{
			PlayAnimation(SuperFlyingAnimation, 0.f, 1, EUMGSequencePlayMode::Forward, 1.f);
		}

	}
	if (!SuperFlyOn)
	{
		SuperFly->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UGameHUDWidget::Distance()
{
	
}


//Used to Create a list of Animation to store and used later
void UGameHUDWidget::StoreWidgetAnimation()
{
	AnimationMap.Empty();

	UProperty* Prop = GetClass()->PropertyLink;
	
	while (Prop)
	{
		//Grabs Object Propertys only
		if (Prop->GetClass() == UObjectProperty::StaticClass())
		{
			UObjectProperty* ObjProp = Cast<UObjectProperty>(Prop);

			//Only grab widget animations
			if (ObjProp->PropertyClass == UWidgetAnimation::StaticClass())
			{
				UObject* obj = ObjProp->GetObjectPropertyValue_InContainer(this);
				UWidgetAnimation* WidgetAnimation = Cast<UWidgetAnimation>(obj);

				if (WidgetAnimation && WidgetAnimation->MovieScene)
				{
					FName AnimName = WidgetAnimation->MovieScene->GetFName();
					AnimationMap.Add(AnimName, WidgetAnimation);
				}
			}
		}
		Prop = Prop->PropertyLinkNext;
	}
}
//used to call animation by name to the Widget
UWidgetAnimation* UGameHUDWidget::GetAnimationByName(FName AnimationName) const
{
	UWidgetAnimation* const* WidgetAnimation = AnimationMap.Find(AnimationName);
	if (WidgetAnimation)
	{
		return *WidgetAnimation;
	}
	return nullptr;
}


