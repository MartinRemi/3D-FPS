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

void UGameInputManager::getResolutionFromConfig(FString & resolution)
{
	UGameUserSettings* Settings = GetGameUserSettings();
	if (!Settings)
	{
		exit(-42);
	}
	FIntPoint res = Settings->GetLastConfirmedScreenResolution();
	resolution = FString::FromInt(res.X) + "x" + FString::FromInt(res.Y);
}

void UGameInputManager::getAvailableResolutions(TArray<FString>& resolutions, bool & success)
{
	FScreenResolutionArray ResolutionsArray;

	if (RHIGetAvailableResolutions(ResolutionsArray, true))  // "RHI" dependency
	{
		for (const FScreenResolutionRHI& Resolution : ResolutionsArray)
		{
			FString StrW = FString::FromInt(Resolution.Width);
			FString StrH = FString::FromInt(Resolution.Height);
			resolutions.AddUnique(StrW + "x" + StrH);
		}

		success = true;
		return;
	}
	success = false;
}

UGameUserSettings* UGameInputManager::GetGameUserSettings()
{
	if (GEngine != nullptr)
	{
		return GEngine->GameUserSettings;
	}

	return nullptr;
}

