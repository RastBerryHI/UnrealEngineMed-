// Fill out your copyright notice in the Description page of Project Settings.

#include "DrawDebugHelpers.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.h"

// Two out parameters
#define OUT

UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	
	HandleComponent = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	FindComponent(HandleComponent);
	SetUpBindings();
}

void UGrabber::Release() 
{
	UE_LOG(LogTemp, Error, TEXT("Action released"));
	HandleComponent->ReleaseComponent();
}

void UGrabber::Grab()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	// OUT Parameters:
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	FString Location = PlayerViewPointLocation.ToString();
	FString Rotation = PlayerViewPointRotation.ToString();

	// Third param
	FVector LineEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	UE_LOG(LogTemp, Error, TEXT("Action Happend"));

	FHitResult Hit = RayCast();
	UPrimitiveComponent* ComponentToGrab = Hit.GetComponent();

	if (Hit.GetActor()) 
	{
		HandleComponent->GrabComponent
		(
			ComponentToGrab,
			NAME_None,
			LineEnd,
			true
		);
	}
}

void UGrabber::SetUpBindings() 
{
	// INPUT!
	if (InputComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("InputComponent has been set up on %s"), *GetOwner()->GetName());

		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("There is no InputComponent has been set up on %s"), *GetOwner()->GetName());
		
	}
}

void UGrabber::FindComponent(UActorComponent* ActorComponent) 
{
	// HANDLE!
	if (ActorComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Component has been set up on %s"), *GetOwner()->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("There is no Component has been set up on "));
	}
}

FVector UGrabber::GetLineEnd() 
{	
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

		// OUT Parameters:
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	// Third param
	FVector LineEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	return LineEnd;
}

FVector UGrabber::GetPlayerViewPointLocation() 
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	// OUT Parameters:
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	return PlayerViewPointLocation;
}

FHitResult UGrabber::RayCast() 
{
	// First param
	FHitResult Hit;

	// Fifth param
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	// Actual RayCast function
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		GetPlayerViewPointLocation(),
		GetLineEnd(),
		// Forth param
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);
	

	// DEBUG:
	//AActor* Actor = Hit.GetActor();
	//if (Actor)
	//{
	//	UE_LOG(LogTemp, Error, TEXT("Hit: %s"), *(Actor->GetName()));
	//}

	///*DrawDebugLine(
	//	GetWorld(),
	//	GetPlayerViewPointLocation(),
	//	GetLineEnd(),
	//	FColor(0, 255, 0),
	//	false,
	//	0.f,
	//	10.f*/
	//);

	return Hit;
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (HandleComponent->GrabbedComponent) 
	{
		HandleComponent->SetTargetLocation(GetLineEnd());
	}
	
}

