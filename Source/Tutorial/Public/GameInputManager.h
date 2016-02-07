// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Weapon.h"
#include "GameInputManager.generated.h"

/**
 * 
 */
UCLASS(Config = Game)
class TUTORIAL_API UGameInputManager : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "GameInputManager")
	static void saveResolutionToConfig(FString resolution);

	UFUNCTION(BlueprintCallable, Category = "GameInputManager")
	static void saveScreenModeToConfig(FString screenMode);

	UFUNCTION(BlueprintCallable, Category = "GameInputManager")
	static void getResolutionFromConfig(FString & resolution);

	UFUNCTION(BlueprintCallable, Category = "GameInputManager")
	static void getAvailableResolutions(TArray<FString>& resolutions, bool & success);

	static UGameUserSettings* GetGameUserSettings();
	
};
