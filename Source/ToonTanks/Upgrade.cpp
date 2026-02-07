// Fill out your copyright notice in the Description page of Project Settings.
#include "Upgrade.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"



// Sets default values
AUpgrade::AUpgrade()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent=CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent=BoxComponent;

	StaticMeshComponent=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMeshComponent->SetupAttachment(BoxComponent);
}

// Called when the game starts or when spawned
void AUpgrade::BeginPlay()
{
	Super::BeginPlay();
	
}

