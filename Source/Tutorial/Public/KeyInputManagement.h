// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "KeyInputManagement.generated.h"

/**
 * 
 */
UCLASS()
class TUTORIAL_API UKeyInputManagement : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Input")
		static void changeInput(APlayerController * pController, FKey newKey, FName actionName, bool invert = false);
	
};
