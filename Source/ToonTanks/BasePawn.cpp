// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"
#include "Upgrade.h"   

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Colider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(CapsuleComp);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void ABasePawn::HandleDestruction()
{
	if(UpgradeClass){
		auto Actor = GetWorld()->SpawnActor<AUpgrade>(UpgradeClass,GetActorLocation(),GetActorRotation());
	}
	
	//visual effects
	if(DeathParticules)	UGameplayStatics::SpawnEmitterAtLocation(this,DeathParticules,GetActorLocation(),GetActorRotation());
	
	if(DeathSound) UGameplayStatics::PlaySoundAtLocation(this,DeathSound,GetActorLocation());

	if(DeathCameraShakeClass) GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass);
}


void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	FVector ToTarget=LookAtTarget-TurretMesh->GetComponentLocation()+FVector(0,0,-75);
	//FRotator LookAtRotation = FRotator(0.f,ToTarget.Rotation().Yaw,0.f);
	TurretMesh->SetWorldRotation(FMath::RInterpTo(TurretMesh->GetComponentRotation(),ToTarget.Rotation(),UGameplayStatics::GetWorldDeltaSeconds(this),5.f));
}

void ABasePawn::Firer()
{
	if(ProjectileClass){
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass,ProjectileSpawnPoint->GetComponentLocation(),ProjectileSpawnPoint->GetComponentRotation());
	Projectile->SetOwner(this);
	}
}

void ABasePawn::RotateBaseMesh(FRotator DeltaRotation)
{
	BaseMesh->AddWorldRotation(DeltaRotation);
}

