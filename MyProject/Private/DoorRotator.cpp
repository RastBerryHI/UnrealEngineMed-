// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"
#include "Components/AudioComponent.h"
#include "GameFramework//PlayerController.h"
#include <MyProject\Public\DoorRotator.h>
#include <Runtime\Engine\Classes\Engine\TriggerVolume.h>
#include "DoorRotator.h"

#define OUT

// Sets default values for this component's properties
UDoorRotator::UDoorRotator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UDoorRotator::BeginPlay()
{
	Super::BeginPlay();

	if (TriggerVolume == nullptr) 
	{
		
		FString name = GetOwner()->GetName();
		UE_LOG(LogTemp, Error, TEXT("%s has the open door component, but no TriggerVolume"), *name);
	}

	Player = GetWorld()->GetFirstPlayerController()->GetPawn();
	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	TargetYaw = InitialYaw + 90.f;
	DoorLastOpened = 0.f;
	ShutDelay = 2.f;
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();
}


// Called every frame
void UDoorRotator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(TotalMassOfActor() > Mass)
	{
		OpenDoor(DeltaTime);
		DoorLastOpened = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f"), DoorLastOpened);
	}
	else if (TriggerVolume && TriggerVolume->IsOverlappingActor(Player) == false)
	{
		if (GetWorld()->GetTimeSeconds() - DoorLastOpened > ShutDelay)
		{
			CloseDoor(DeltaTime);
		}
	}
}


float UDoorRotator::TotalMassOfActor() const
{
	float TotalMass = 0.f;
	TArray<AActor*> OUT OverlappingActors;
	TriggerVolume->GetOverlappingActors(OUT OverlappingActors);

	for(AActor* Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Actor->GetName());
	}


	return TotalMass;
}

void UDoorRotator::PlayOpenSound() 
{
	if (isClosed == true)
	{
		if (!AudioComponent->IsPlaying())
		{
			AudioComponent->Play();
		}

		isClosed = false;
	}
}

void UDoorRotator::PlayCloseSound()
{
	if (isClosed == false)
	{
		if (!AudioComponent->IsPlaying())
		{
			AudioComponent->Play();
		}

		isClosed = true;
	}
}

void UDoorRotator::OpenDoor(float time) 
{
	CurrentYaw = FMath::Lerp(CurrentYaw, TargetYaw, time * 1.f);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);

	PlayOpenSound();
}

void UDoorRotator::CloseDoor(float time) 
{
	CurrentYaw = FMath::Lerp(CurrentYaw, InitialYaw, time * 2.f);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);

	PlayCloseSound();
}

