// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PawnMovementComponent.h"
#include "AnotherCharacter.h"
#include "RunTime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Animation/AnimMontage.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsAttack = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsPlaySound = false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UAnimMontage* AnimMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		UAnimMontage* Agression;
	
	void Attack();

	void Agress();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool bAcceptsSecondAttackInput;

protected:
	/*True means that we're currently in air - or falling*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bIsFalling;

	/*Holds the current speed of our character*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float MovementSpeed;

	/*Updates the above properties*/
	UFUNCTION(BlueprintCallable, Category = "UpdateAnimationProperties")
		void UpdateAnimationProperties();
};
