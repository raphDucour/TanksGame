// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "Kismet/GameplayStatics.h"

ATankPlayer::ATankPlayer()
{
	ArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm"));
    ArmComponent->SetupAttachment(RootComponent);

    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camra"));
    CameraComponent->SetupAttachment(ArmComponent);

	bUseControllerRotationPitch = true;
}

void ATankPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	/*FHitResult HitResult;
	if(TankPlayerController){
		TankPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility,false,HitResult);
		RotateTurret(HitResult.ImpactPoint);
	}*/
}


void ATankPlayer::HandleDestruction()
{
	Super::HandleDestruction();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);

	bAlive = false;
}

	

void ATankPlayer::BeginPlay()
{

    Super::BeginPlay();
	
	BaseMesh->SetAbsolute(false, true, false);
	TurretMesh->SetAbsolute(false, false, false);

	TankPlayerController= Cast<APlayerController>(GetController());

    if (TankPlayerController)
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(TankPlayerController->GetLocalPlayer()))
        {
            if (InputMappingContext)
            {
                Subsystem->AddMappingContext(InputMappingContext, 0);
                UE_LOG(LogTemp, Warning, TEXT("InputMappingContext added!"));
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("InputMappingContext is null!"));
            }
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to get EnhancedInputLocalPlayerSubsystem!"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("PlayerController is null!"));
    }

	if(TankPlayerController->PlayerCameraManager){
		TankPlayerController->PlayerCameraManager->ViewPitchMin = -20.0f;  // Limite vers le bas
        TankPlayerController->PlayerCameraManager->ViewPitchMax = 20.0f;   // Limite vers le haut
	}
}



// Called to bind functionality to input
void ATankPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
        EnhancedInputComponent->BindAction(Move, ETriggerEvent::Triggered, this, &ATankPlayer::Mover);
	    EnhancedInputComponent->BindAction(Rotate, ETriggerEvent::Triggered, this, &ATankPlayer::Rotator);
	    EnhancedInputComponent->BindAction(Fire, ETriggerEvent::Started, this, &ATankPlayer::Firer);
	    UE_LOG(LogTemp,Warning, TEXT("'%s', lets go!"), *GetNameSafe(this));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ATankPlayer::Mover(const FInputActionValue& Value)
{
    FVector2D V = Value.Get<FVector2D>();
	if (Controller != nullptr)
		{
			float TargetYaw = FMath::Atan2(V.Y, V.X) * (180.f / PI);
			RotateBaseMesh(FRotator(0,-TargetYaw+(TurretMesh->GetComponentRotation()).Yaw+90,0),5.f);

			AddMovementInput(GetActorForwardVector(), V.Y);
			AddMovementInput(GetActorRightVector(), V.X);// add movement 
			}
}

void ATankPlayer::Rotator(const FInputActionValue& Value)
{
	FVector2D V = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(V.X/2);
		AddControllerPitchInput(-V.Y/2);
		// Calcul de l'angle à partir du joystick
        //float TargetYaw = FMath::Atan2(V.X, V.Y) * (180.f / PI);

        // Appliquer la rotation à la tourelle (uniquement sur l'axe Yaw)
        //FRotator NewRotation = FRotator(0.f, -TargetYaw+180.f, 0.f)+GetActorRotation();
		//TurretMesh->SetWorldRotation(NewRotation);
	}
	else{UE_LOG(LogTemp, Warning, TEXT("No controller"));}
}


void ATankPlayer::ChangeSpeed(float NewSpeed)
{
	Speed=NewSpeed;
	if(Speed>200) Speed=200;
}
