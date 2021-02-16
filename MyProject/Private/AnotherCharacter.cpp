// Fill out your copyright notice in the Description page of Project Settings.
// code By Sir_Collagen: inst @sir_collagen

#include "AnotherCharacter.h"

// Sets default values
AAnotherCharacter::AAnotherCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.f);
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	CameraComponent->AttachTo(GetMesh(), FName("Head"));
	CameraComponent->bUsePawnControlRotation = true;
	MeleeZone = CreateDefaultSubobject<UBoxComponent>(TEXT("MeleeZone"));
	MeleeZone->AttachTo(GetMesh(), FName("Head"));
}

// Called when the game starts or when spawned
void AAnotherCharacter::BeginPlay()
{
	Super::BeginPlay();
}

int32 AAnotherCharacter::SetHealth(int32 Damage) 
{
	Health -= Damage;
	if(Health > 100)
	{
		Health = 100;
	}
	else if (Health < 0) 
	{
		Health = 0;
	}

	return Health;
}

void AAnotherCharacter::AttackAction()
{
	UMyAnimInstance* AnimInstance = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance());
	
	if (AnimInstance)
		AnimInstance->Attack();	
	else
		UE_LOG(LogTemp, Error, TEXT("No AnimInstacne component in %s"), *GetOwner()->GetName());
}

void AAnotherCharacter::AgressionAction() 
{
	UMyAnimInstance* AnimInstance = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance());

	if (AnimInstance)
		AnimInstance->Agress();
	else
		UE_LOG(LogTemp, Error, TEXT("No AnimInstacne component in %s"), *GetOwner()->GetName());
}

void AAnotherCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	// Here I call Function which calls function from UMyAnimInstance	
	PlayerInputComponent->BindAction("Melee", IE_Pressed, this, &AAnotherCharacter::AttackAction);

	// Mouse Axis Binding
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);

	// Keyboard axis binding
	PlayerInputComponent->BindAxis("Forward", this, &AAnotherCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Right", this, &AAnotherCharacter::MoveRight);	
}


// Called every frame
void AAnotherCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


// Called to bind functionality to input

void AAnotherCharacter::MoveForward(float Val)
{
	if (Val != 0) 
	{
		AddMovementInput(GetActorForwardVector(), Val);
	}
}

void AAnotherCharacter::MoveRight(float Val)
{
	if (Val != 0)
	{
		AddMovementInput(GetActorRightVector(), Val);
	}
}


