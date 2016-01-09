// Fill out your copyright notice in the Description page of Project Settings.

#include "Tutorial.h"
#include "Weapon.h"


// Sets default values
AWeapon::AWeapon() :
	SocketWeaponMuzzle(TEXT("weapon_projectile")),
	FireRate(1.0f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

