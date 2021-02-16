// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/AudioComponent.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "DoorRotator.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UDoorRotator : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorRotator();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	float TargetYaw;
	float InitialYaw;
	float CurrentYaw;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenDoor(float time);
	void CloseDoor(float time);
	void PlayOpenSound();
	void PlayCloseSound();
	float TotalMassOfActor() const;

private:
	UPROPERTY(EditAnywhere)
	ATriggerVolume* TriggerVolume;

	UPROPERTY(EditAnywhere)
	AActor* Player;

	UPROPERTY()
	UAudioComponent* AudioComponent;

	UPROPERTY(EditAnywhere)
	float Mass;

	float DoorLastOpened;
	float ShutDelay;

	//bool isOpen = false;
	bool isClosed = true;
};
