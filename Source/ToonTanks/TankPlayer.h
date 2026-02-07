// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankCharacter.h"
#include "InputActionValue.h"
#include "TankPlayer.generated.h"
/**
 * 
 */
UCLASS()
class TOONTANKS_API ATankPlayer : public ATankCharacter
{
	GENERATED_BODY()

public:
	ATankPlayer();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

	APlayerController* GetTankPlayerController() const{return TankPlayerController;}

	bool bAlive = true;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ChangeMeshAndProjectileClass(int numTank);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateHealthBar(float NewHealth);

	UFUNCTION(BlueprintCallable)
	void ChangeSpeed(float NewSpeed);


protected:

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;

	
	
private :

	UPROPERTY(EditAnywhere, Category="Caracteristics")
	float Speed= 70;

	UPROPERTY(EditAnywhere, Category="Caracteristics")
	float TurnRate= 100;

	UPROPERTY(VisibleAnywhere, Category="Components")
	class USpringArmComponent* ArmComponent;

	UPROPERTY(VisibleAnywhere, Category="Components")
	class UCameraComponent* CameraComponent;
	



	UPROPERTY(EditAnywhere, Category = "Input")
    class UInputMappingContext* InputMappingContext;

    UPROPERTY(EditAnywhere, Category = "Input")
    class UInputAction* Move;

	UPROPERTY(EditAnywhere, Category = "Input")
    class UInputAction* Rotate;

	UPROPERTY(EditAnywhere, Category = "Input")
    class UInputAction* Fire;
	
	
	void Mover(const FInputActionValue& Value);
	void Rotator(const FInputActionValue& Value);

	APlayerController* TankPlayerController;
};
