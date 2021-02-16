// Fill out your copyright notice in the Description page of Project Settings.

#include "AIPatrolController.h"
#include "AIPatrol.h"
#include "PatrolPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"


AAIPatrolController::AAIPatrolController()
{
	// Initialize blackboard and behavior tree
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

	// Initialize bleackboard keys
	PlayerKey = "Target";
	LocationToGoKey = "LocationToGo";

	CurrentPatroPoint = 0;
}


void AAIPatrolController::OnPossess(APawn * InPawn)
{
	Super::OnPossess(InPawn);
	
	//// Get reference to the character
	AAIPatrol* AICharatcer = Cast<AAIPatrol>(InPawn);


	if (AICharatcer) 
	{

		if (AICharatcer->BehaviourTree->BlackboardAsset) 
		{
			BlackboardComp->InitializeBlackboard(*(AICharatcer->BehaviourTree->BlackboardAsset));
		}

		/* Populate patrol point array */
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APatrolPoint::StaticClass(), PatrolPoints);

		BehaviorTreeComp->StartTree(*AICharatcer->BehaviourTree);

	}
}

void AAIPatrolController::SetPlayerCaught(APawn * InPawn)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(PlayerKey, InPawn);
	}
}

