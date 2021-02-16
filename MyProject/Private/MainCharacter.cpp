// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	CameraComponent->bUsePawnControlRotation = true;
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("SimpleAction", IE_Pressed, this, &AMainCharacter::SimpleAction);
	PlayerInputComponent->BindAction("SimpleAction", IE_Released, this, &AMainCharacter::SimpleAction);

	// Mouse Axis Binding
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);

	// Keyboard axis binding
	PlayerInputComponent->BindAxis("Forward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Right", this, &AMainCharacter::MoveRight);
}

void AMainCharacter::MoveForward(float Val)
{
	if (Val != 0)
	{
		AddMovementInput(GetActorForwardVector(), Val);
	}
}

void AMainCharacter::MoveRight(float Val)
{
	if (Val != 0)
	{
		AddMovementInput(GetActorRightVector(), Val);
	}
}

void AMainCharacter::SimpleAction()
{
	UE_LOG(LogTemp, Warning, TEXT("E was pressed"));
}

void AMainCharacter::SimpleActionRelease()
{
	UE_LOG(LogTemp, Warning, TEXT("E was released"));
}
