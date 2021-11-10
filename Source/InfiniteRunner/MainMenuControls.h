// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainMenuControls.generated.h"

/**
 * 
 */
UCLASS()
class INFINITERUNNER_API AMainMenuControls : public APlayerController
{
	GENERATED_BODY()

protected:
   virtual void OnBeginPlay();


};
