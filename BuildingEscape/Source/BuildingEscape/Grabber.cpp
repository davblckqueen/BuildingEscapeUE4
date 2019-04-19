// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber is ready!!"));
	
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	
	if (PhysicsHandle)
	{
		UE_LOG(LogTemp, Warning, TEXT("Se encontro componente con fisicas en %s ."), *(GetOwner()->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No se encuentra componente con fisicas en %s ."), *(GetOwner()->GetName()));
	}

	///Solo lee cuando se depura el juego.
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Se encontro InputComponent."));
		//Bind the Input Access / Vincular el comando de entrada.
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No se encuentra InputComponent."));
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab is pressed / Se presiono Grab."));
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Get player point view this tick
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotator;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotator
	);
	//TODO log out to test
	/*UE_LOG(LogTemp, Warning, TEXT("PointView: P: %s R: %s"), 
		*PlayerViewPointLocation.ToString(), 
		*PlayerViewPointRotator.ToString()
	);*/

	
	
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotator.Vector() * Reach;
	///Draw a red trace in the world to visualice it
	DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(255, 0, 0, 1),
		false,
		0.f,
		0.f,
		10.f
	);
	///Setup query parameters
	FCollisionQueryParams TraceParemeters(FName(TEXT("")), false, GetOwner());

	///Line-Trace (AKA Ray-cast) out to search distance
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParemeters
	);
	//See what we  hit
	AActor *ActorHit = Hit.GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Mi rayo golpea: %s"), *(ActorHit->GetName()));
	}
}



