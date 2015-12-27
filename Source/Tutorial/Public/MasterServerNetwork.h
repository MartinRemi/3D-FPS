// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Networking.h"
#include <string>
#include "MasterServerNetwork.generated.h"

/**
 * 
 */
UCLASS()
class TUTORIAL_API UMasterServerNetwork : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

private:
	static FString address;
	static int32 port;
	
public:
	UFUNCTION(BlueprintCallable, Category = "MasterServer")
		static void requestServer(FString & ip, int32 & port, bool & success);

	UFUNCTION(BlueprintCallable, Category = "MasterServer")
		static void registerAsServer(int32 port, bool & success);

	UFUNCTION(BlueprintCallable, Category = "MasterServer")
		static void unregister(int32 port, bool & success);
};
