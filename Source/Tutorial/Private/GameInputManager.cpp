// Fill out your copyright notice in the Description page of Project Settings.

#include "Tutorial.h"
#include "GameInputManager.h"


void UGameInputManager::saveResolutionToConfig(FString resolution)
{
	FString sWidth, sHeight;
	if (!resolution.Split("x", &sWidth, &sHeight))
		return;
	UGameUserSettings* Settings = GetGameUserSettings();
	if (!Settings)
	{
		exit(-42);
	}
	Settings->SetScreenResolution(FIntPoint(FCString::Atoi(*sWidth), FCString::Atoi(*sHeight)));
	Settings->ConfirmVideoMode();
	Settings->SaveSettings();
}

void UGameInputManager::saveScreenModeToConfig(FString screenMode)
{
	UGameUserSettings* Settings = GetGameUserSettings();
	if (!Settings)
	{
		exit(-42);
	}
	Settings->SetFullscreenMode(screenMode != "w" ? EWindowMode::Fullscreen : EWindowMode::Windowed);
	Settings->ConfirmVideoMode();
	Settings->SaveSettings();
}

UGameUserSettings* UGameInputManager::GetGameUserSettings()
{
	if (GEngine != nullptr)
	{
		return GEngine->GameUserSettings;
	}

	return nullptr;
}

