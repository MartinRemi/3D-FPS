// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class TUTORIAL_API AWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeapon();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UStaticMesh* StaticMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FName SocketCharacteHand;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		FName SocketWeaponMuzzle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		float FireRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UParticleSystem* ParticleFire;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		USoundCue* SoundFire;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		int32 AmmoMax;

};
