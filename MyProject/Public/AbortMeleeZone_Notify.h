// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnotherCharacter.h"
#include "AbortMeleeZone_Notify.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UAbortMeleeZone_Notify : public UAnimNotify
{
	GENERATED_BODY()
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
