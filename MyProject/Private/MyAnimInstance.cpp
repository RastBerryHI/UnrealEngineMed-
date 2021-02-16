// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"

void UMyAnimInstance::UpdateAnimationProperties()
{

	APawn* Pawn = TryGetPawnOwner();
	
	if (Pawn)// && Character) 
	{
		if (Pawn)
		{
			//bIsAttack = Character->bIsAttack;
			MovementSpeed = Pawn->GetVelocity().Size();
			UPawnMovementComponent* MovementComponent = Pawn->GetMovementComponent();
			bIsFalling = MovementComponent->IsFalling();
		}
	}
}

void UMyAnimInstance::Attack() 
{
	if (AnimMontage)
	{
		FName CurrentSection = Montage_GetCurrentSection(AnimMontage);
		
		if (CurrentSection.IsNone())
		{
			UE_LOG(LogTemp, Error, TEXT("CurrentSection is None"));
			Montage_Play(AnimMontage);
		}
		else if (CurrentSection.IsEqual("SaveAttack") && bAcceptsSecondAttackInput) 
		{
			UE_LOG(LogTemp, Error, TEXT("CurrentSection is Default"));
			bAcceptsSecondAttackInput = false;
		}
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("No AnimMontage"));
	}
}

void UMyAnimInstance::Agress() 
{
	if (Agression) 
	{
		Montage_Play(Agression);
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("No Agression Animation"));
	}
}


