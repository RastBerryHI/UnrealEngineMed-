// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPatrol.h"
#include "AIPatrolController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Pawn.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
AAIPatrol::AAIPatrol()
{
	// Initialize senses
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	PawnSensingComp->SetPeripheralVisionAngle(90.f);
}

// Called when the game starts or when spawned
void AAIPatrol::BeginPlay()
{
	Super::BeginPlay();
	
	if (PawnSensingComp) 
	{
		PawnSensingComp->OnSeePawn.AddDynamic(this, &AAIPatrol::OnPlayerCaught);
	}
}

// Called to bind functionality to input
void AAIPatrol::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AAIPatrol::OnPlayerCaught(APawn* Pawn)
{
	AAIPatrolController* AIController = Cast<AAIPatrolController>(GetController());

	if (AIController) 
	{
		UE_LOG(LogTemp, Error, TEXT("You have been caught"));
		AIController->SetPlayerCaught(Pawn);
	}
}

