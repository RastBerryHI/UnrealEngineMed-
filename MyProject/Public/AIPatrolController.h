// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "GameFramework/Pawn.h"
#include "AIPatrolController.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AAIPatrolController : public AAIController
{
	GENERATED_BODY()

private:
		
	UBlackboardComponent* BlackboardComp;

	UBehaviorTreeComponent* BehaviorTreeComp;

	/*Blackboard Keys*/
	UPROPERTY(EditDefaultsOnly, Category = AI)
	FName LocationToGoKey;

	UPROPERTY(EditDefaultsOnly, Category = AI)
	FName PlayerKey;

	// Collection of patrol points
	TArray<AActor*> PatrolPoints;


	virtual void OnPossess(APawn* InPawn) override;


public:	
	
	AAIPatrolController();

	FORCEINLINE UBlackboardComponent* GetBlackboardComponent() const { return BlackboardComp; }

	FORCEINLINE TArray<AActor*> GetPatrolPoints() const { return PatrolPoints; }

	void SetPlayerCaught(APawn* InPawn);

	int32 CurrentPatroPoint = 0;
};
