// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankCharacter.h"
#include "TankEvilCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATankEvilCharacter : public ATankCharacter
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
    ATankEvilCharacter();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

	UFUNCTION(BlueprintCallable)
	void RotateTurretMesh(FRotator DeltaRotation, float vitesse);

private:
};
