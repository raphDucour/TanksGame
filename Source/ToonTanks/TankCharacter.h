// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GeometryCollection/GeometryCollectionActor.h"
#include "GameFramework/Character.h"
#include "TankCharacter.generated.h"

UCLASS()
class TOONTANKS_API ATankCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATankCharacter();

	void HandleDestruction();
	
	UFUNCTION(BlueprintCallable)
	void Firer();

	UPROPERTY(BlueprintReadWrite)
	int NumBullets=1;

	UPROPERTY(BlueprintReadWrite)
	float DistanceBetweenProjectiles = 40.0f;
	
	UPROPERTY(BlueprintReadWrite)
	bool ActiveRecoil= true;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess="true"))
	UStaticMeshComponent* TurretMesh;
	
	void RotateBaseMesh(FRotator DeltaRotation, float vitesse);
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Combat")
	TSubclassOf<class AProjectile> ProjectileClass;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess="true"))
	UStaticMeshComponent* BaseMesh;

	
private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess="true"))
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere,Category="Combat")
	class UParticleSystem* DeathParticules;

	UPROPERTY(EditAnywhere,Category="Combat")
	class USoundBase* DeathSound;

	UPROPERTY(EditAnywhere,Category="Combat")
	TSubclassOf<class UCameraShakeBase> DeathCameraShakeClass;

	UPROPERTY(EditAnywhere, Category="Explosion")
	TSubclassOf<AGeometryCollectionActor> GeometryCollectionActor;

	bool CanFire=true;
	void ResetFire();
	void FireBullets(int BulletsCount,float hauteur);
	void Fire1BulletAtLocation(FVector Location);


	void AddRecoil(float power);
	void LittleRecoil();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
