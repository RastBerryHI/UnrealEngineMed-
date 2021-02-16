// Fill out your copyright notice in the Description page of Project Settings.
// code By Sir_Collagen: inst @sir_collagen

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "Components/MeshComponent.h"
#include "Components/InputComponent.h"
#include "MyAnimInstance.h"
#include "Components/BoxComponent.h"
#include "OpenMeleeZone_Notify.h"
#include "AnotherCharacter.generated.h"

class UInputComponent;

UCLASS()
class MYPROJECT_API AAnotherCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* MeleeZone;

	int32 Health = 100;

public:
	// Sets default values for this character's properties
	AAnotherCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsPlaySound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Damage = 35;

	UFUNCTION(BlueprintCallable, Category = "GetHealth")
		int32 GetHealth() { return Health; }

	UFUNCTION(BlueprintCallable, Category = "SetHealth")
		int32 SetHealth(int32 Damage);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Val);
	void MoveRight(float Val);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category="AttackAction")
	void AttackAction();

	UFUNCTION(BlueprintCallable, Category = "AgressionAction")
		void AgressionAction();
};
