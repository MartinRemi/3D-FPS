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

	static UGameUserSettings* GetGameUserSettings();
	
};
