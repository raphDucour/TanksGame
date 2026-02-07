// Fill out your copyright notice in the Description page of Project Settings.


#include "TankCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Projectile.h"

// Sets default values
ATankCharacter::ATankCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(RootComponent);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

// Called when the game starts or when spawned
void ATankCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATankCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATankCharacter::HandleDestruction()
{
	//visual effects
	if(DeathParticules)	UGameplayStatics::SpawnEmitterAtLocation(this,DeathParticules,GetActorLocation(),GetActorRotation());
	
	if(DeathSound) UGameplayStatics::PlaySoundAtLocation(this,DeathSound,GetActorLocation());

	if(DeathCameraShakeClass) GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass);

	TurretMesh->DestroyComponent();
	SetActorEnableCollision(false);
	if(GeometryCollectionActor){
		AGeometryCollectionActor* Explosion = GetWorld()->SpawnActor<AGeometryCollectionActor>(GeometryCollectionActor,GetActorLocation(),BaseMesh->GetComponentRotation());
	}
}



void ATankCharacter::Firer()
{
	if(ProjectileClass && CanFire){
		//Cannot Fire for 0.5s
		CanFire=false;
		FTimerHandle FireRateTimerHandle;
		GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &ATankCharacter::ResetFire, 0.5f, false);

		FireBullets(NumBullets,0);//fire
		LittleRecoil();//meshRecoil

		if(ActiveRecoil)//tankRealRecoil
		{
			float RelativeRotation =FMath::Abs(BaseMesh->GetComponentRotation().Yaw-TurretMesh->GetComponentRotation().Yaw);
			if(RelativeRotation>95){AddRecoil(RelativeRotation-95);}
		}
	}
}

void ATankCharacter::ResetFire()
{
    CanFire = true;
}








void ATankCharacter::RotateBaseMesh(FRotator DeltaRotation, float vitesse)
{
	FRotator NewRotation = FMath::RInterpTo(BaseMesh->GetComponentRotation(), DeltaRotation, GetWorld()->GetDeltaSeconds(), vitesse);
	BaseMesh->SetWorldRotation(NewRotation);
}


void ATankCharacter::AddRecoil(float power){
	power=FMath::Sqrt(FMath::Sqrt(power));
	FVector ImpulseDirection = -(TurretMesh->GetComponentRotation()).Vector()*300*power+FVector(0.f,0.f,60*power);  // Exemple d'impulsion vers le haut
	LaunchCharacter(ImpulseDirection, false, false);
}

void ATankCharacter::LittleRecoil()
{
	// Récupérer la position actuelle de la tourelle
	FVector FirstLocation = TurretMesh->GetRelativeLocation();
	// Définir la direction du recul en fonction de la rotation de la tourelle
	FRotator TurretRotation = TurretMesh->GetRelativeRotation();
	FVector ReculDirection = TurretRotation.Vector(); // Obtient le vecteur avant de la tourelle
	// Calculer la nouvelle position avec le recul
	float ReculIntensity = 20.0f; 
	FVector ReculLocation = FirstLocation - (ReculDirection * ReculIntensity);
	TurretMesh->SetRelativeLocation(ReculLocation);
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, FirstLocation](){TurretMesh->SetRelativeLocation(FirstLocation);}, 0.1f, false);
}


void ATankCharacter::FireBullets(int BulletsCount,float hauteur){
	FVector HauteurLocation= FVector(0,0,hauteur);
	if(BulletsCount==1){
		//fire 1 bullet
		Fire1BulletAtLocation(ProjectileSpawnPoint->GetComponentLocation()+HauteurLocation);
	}
	else if(BulletsCount==2){
		FVector RightDistance=ProjectileSpawnPoint->GetRightVector()*DistanceBetweenProjectiles;
		
		Fire1BulletAtLocation(ProjectileSpawnPoint->GetComponentLocation()+RightDistance/2+HauteurLocation);
		Fire1BulletAtLocation(ProjectileSpawnPoint->GetComponentLocation()-RightDistance/2+HauteurLocation);
	}
	else if(BulletsCount==3){
		FVector RightDistance=ProjectileSpawnPoint->GetRightVector()*DistanceBetweenProjectiles;

		Fire1BulletAtLocation(ProjectileSpawnPoint->GetComponentLocation()+HauteurLocation);
		Fire1BulletAtLocation(ProjectileSpawnPoint->GetComponentLocation()+RightDistance + HauteurLocation);
		Fire1BulletAtLocation(ProjectileSpawnPoint->GetComponentLocation()-RightDistance + HauteurLocation);
	}
	else if(BulletsCount==4){
		FireBullets(3,0);
		FireBullets(1,DistanceBetweenProjectiles);
	}
	else if(BulletsCount==5){
		FireBullets(3,0);
		FireBullets(2,DistanceBetweenProjectiles);
	}
	else if(BulletsCount==6){
		FireBullets(3,0);
		FireBullets(3,DistanceBetweenProjectiles);
	}
}

void ATankCharacter::Fire1BulletAtLocation(FVector Location){
	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass,Location,ProjectileSpawnPoint->GetComponentRotation());
	Projectile->SetOwner(this);
}