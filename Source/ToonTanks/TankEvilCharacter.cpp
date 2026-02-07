// Fill out your copyright notice in the Description page of Project Settings.


#include "TankEvilCharacter.h"


ATankEvilCharacter::ATankEvilCharacter()
{
	
}


void ATankEvilCharacter::BeginPlay()
{
    Super::BeginPlay();

	// Assigner l'AIController par défaut à ce personnage
	if (GetController() == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("pas de controller"));
	}
	BaseMesh->SetAbsolute(false, false, false);
	TurretMesh->SetAbsolute(false,true,false);
}

void ATankEvilCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATankEvilCharacter::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void ATankEvilCharacter::RotateTurretMesh(FRotator DeltaRotation, float vitesse)
{
	FRotator NewRotation = FMath::RInterpTo(TurretMesh->GetComponentRotation(), DeltaRotation, GetWorld()->GetDeltaSeconds(), vitesse);
	TurretMesh->SetWorldRotation(NewRotation);
}