// Fill out your copyright notice in the Description page of Project Settings.


#include "AbortMeleeZone_Notify.h"

void UAbortMeleeZone_Notify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	AAnotherCharacter* Player = Cast<AAnotherCharacter>(MeshComp->GetOwner());
	if (Player)
	{
		UE_LOG(LogTemp, Warning, TEXT("Close"));
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("No pawn at %s"), *(MeshComp->GetName()));
}