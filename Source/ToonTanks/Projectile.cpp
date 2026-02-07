// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	ProjectileMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent=ProjectileMesh;

	MovementComp=CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement Component"));
	MovementComp->MaxSpeed=300.f;
	MovementComp->InitialSpeed=300.f;

	TrailParticules=CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particule Component"));
	TrailParticules->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMesh->OnComponentHit.AddDynamic(this,&AProjectile::OnHit);

	if(LaunchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this,LaunchSound,GetActorLocation());
	}
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp,AActor* OtherActor,UPrimitiveComponent* OtherComp,FVector NormalImpulse,const FHitResult& Hit)
{
	auto MyOwner=GetOwner();
	if(MyOwner==nullptr)return;
	auto OwnerInstigator = MyOwner->GetInstigatorController();

	

	if(OtherActor && OtherActor!=this && OtherActor!=MyOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor,Damage,OwnerInstigator,this,UDamageType::StaticClass());

		if(HitParticules) UGameplayStatics::SpawnEmitterAtLocation(this,HitParticules,GetActorLocation(),GetActorRotation());
		if(HitSound) UGameplayStatics::PlaySoundAtLocation(this,HitSound,GetActorLocation());
		if(HitCameraShakeClass) GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
		
		
		if(NumRebound>1){
			FVector ReflectionVector = FMath::GetReflectionVector(GetActorForwardVector(), Hit.ImpactNormal);
			
			if(ThisActorBlueprintClass)
			{
				AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ThisActorBlueprintClass,GetActorLocation()+ReflectionVector*50+Hit.ImpactNormal*10,ReflectionVector.Rotation());
				Projectile->SetNumRebound(NumRebound-1);
				Projectile->SetOwner(MyOwner);
			}
		}
	}
	
	Destroy();
}

void AProjectile::SetNumRebound(int NewNumRebound){
	NumRebound=NewNumRebound;
}

