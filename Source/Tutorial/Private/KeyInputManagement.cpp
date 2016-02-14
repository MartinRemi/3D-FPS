// Fill out your copyright notice in the Description page of Project Settings.

#include "Tutorial.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerInput.h"
#include "Runtime/Engine/Classes/GameFramework/InputSettings.h"
#include "Runtime/CoreUObject/Public/UObject/UObjectGlobals.h"
#include "KeyInputManagement.h"

void UKeyInputManagement::changeInput(APlayerController * pController, FKey newKey, FName actionName, bool invert)
{
	float scale = (invert) ? -1.0f : 1.0f;

	FInputAxisKeyMapping keyMap(actionName, newKey, scale);
	const UInputSettings* InputSettings = GetDefault<UInputSettings>();

	auto it = pController->PlayerInput->AxisMappings.CreateIterator();
	while(it)
	{
		if (it->Key == newKey)
		{
			((UInputSettings*)InputSettings)->AxisMappings.Remove(*it);
		}
		++it;
	}

	((UInputSettings*)InputSettings)->AddAxisMapping(keyMap);
	((UInputSettings*)InputSettings)->SaveKeyMappings();
}


