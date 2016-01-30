// Fill out your copyright notice in the Description page of Project Settings.

#include "Tutorial.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerInput.h"
#include "Runtime/Engine/Classes/GameFramework/InputSettings.h"
#include "Runtime/CoreUObject/Public/UObject/UObjectGlobals.h"
#include "KeyInputManagement.h"

void UKeyInputManagement::changeInput(APlayerController * pController, FKey newKey, FName actionName)
{
	FInputAxisKeyMapping keyMap(actionName, newKey);
	//const UInputSettings* InputSettings = GetDefault<UInputSettings>();
	//((UInputSettings*)InputSettings)->AddAxisMapping(keyMap);
	//((UInputSettings*)InputSettings)->SaveKeyMappings();
	auto it = pController->PlayerInput->AxisMappings.CreateIterator();
	while(it)
	{
		if (it->Key == newKey)
		{
			pController->PlayerInput->AxisMappings.RemoveAt(it.GetIndex());
		}
		++it;
	}
	pController->PlayerInput->AddAxisMapping(keyMap);
	pController->PlayerInput->SaveConfig();
	//InputSettings->Mapping
}


