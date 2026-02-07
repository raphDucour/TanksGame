// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Upgrade.generated.h"

UCLASS()
class TOONTANKS_API AUpgrade : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUpgrade();

protected:

	

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Composant Box pour la détection de collision
 	UPROPERTY(BlueprintReadOnly, EditAnywhere,Category="component")
 	class UBoxComponent* BoxComponent;


public:	
	

private:
	 
 	
 	// Composant Static Mesh pour l'affichage visuel
 	UPROPERTY(EditAnywhere,Category="component")
 	class UStaticMeshComponent* StaticMeshComponent;

};
