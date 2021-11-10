// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuControls.h"

void AMainMenuControls::OnBeginPlay()
{
	//Sets the Controls for the MainMenu so player can't move
	SetInputMode(FInputModeUIOnly());
}