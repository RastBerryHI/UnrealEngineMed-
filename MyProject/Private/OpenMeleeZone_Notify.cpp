// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenMeleeZone_Notify.h"

void UOpenMeleeZone_Notify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) 
{	
	AAnotherCharacter* Player = Cast<AAnotherCharacter>(MeshComp->GetOwner());
	if (Player) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Open"));
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("No pawn at %s"), *(MeshComp->GetName()));
}