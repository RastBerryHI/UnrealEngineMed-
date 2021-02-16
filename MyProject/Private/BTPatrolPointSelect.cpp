// Fill out your copyright notice in the Description page of Project Settings.

#include "PatrolPoint.h"
#include "AIPatrolController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BTPatrolPointSelect.h"

EBTNodeResult::Type UBTPatrolPointSelect::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIPatrolController* AAICon = Cast<AAIPatrolController>(OwnerComp.GetAIOwner());

	if (AAICon) 
	{
		/* Get blackboard coponent */
		UBlackboardComponent* BlackboardComp = AAICon->GetBlackboardComponent();

		APatrolPoint* CurrentPoint = Cast<APatrolPoint>(BlackboardComp->GetValueAsObject("LocationToGo"));

		TArray<AActor*> AvaliablePatrolPoints = AAICon->GetPatrolPoints();

		APatrolPoint* NextPatrolPoint = nullptr;

		if(AAICon->CurrentPatroPoint != AvaliablePatrolPoints.Num() - 1)
		{
			NextPatrolPoint = Cast<APatrolPoint>(AvaliablePatrolPoints[++AAICon->CurrentPatroPoint]);
		}
		else // if there no points to go to
		{
			NextPatrolPoint = Cast<APatrolPoint>(AvaliablePatrolPoints[0]);
			AAICon->CurrentPatroPoint = 0;
		}

		BlackboardComp->SetValueAsObject("LocationToGo", NextPatrolPoint);

		return EBTNodeResult::Succeeded;

	}

	return EBTNodeResult::Failed;
}
