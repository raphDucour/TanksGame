// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "TankPlayer.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"
#include "TankEvilCharacter.h"



void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();

    HandleGameStart();

    
}
void AToonTanksGameMode::HandleGameStart()
{
    TargetTowers=GetTowerTargetCount();
    Tank = Cast<ATankPlayer>(UGameplayStatics::GetPlayerPawn(this,0));
    TankController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this,0));
    StartGame();

    if(TankController)
    {
        TankController-> SetPlayerEnableState(false);

        FTimerHandle PlayerEnableHandle;
        FTimerDelegate PlayerEnabledelegate = FTimerDelegate::CreateUObject(TankController,&AToonTanksPlayerController::SetPlayerEnableState,true);
        GetWorldTimerManager().SetTimer(PlayerEnableHandle,PlayerEnabledelegate,StartDelay,false);
    }
}




void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
    if(DeadActor==Tank){
        Tank->HandleDestruction();
        if(TankController){
            TankController->SetPlayerEnableState(false);
        }
        GameOver(false);
    }
    else if(ATower* Tower = Cast<ATower>(DeadActor))
    {
        Tower->HandleDestruction();
        --TargetTowers;
        if(TargetTowers<=0)
        {
            GameOver(true);
        }
    }
    else if(ATankEvilCharacter* TankEvil = Cast<ATankEvilCharacter>(DeadActor))
    {
        TankEvil->HandleDestruction();
        --TargetTowers;
        if(TargetTowers<=0)
        {
            GameOver(true);
        }
    }
}



int32 AToonTanksGameMode::GetTowerTargetCount()
{
    TArray<AActor*> Towers;
    UGameplayStatics::GetAllActorsOfClass(this,ATower::StaticClass(),Towers);
    return Towers.Num();

}