// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Grabber.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	//Que tan lejos llegara la linea de trazo.
	float Reach = 100.f;

	UPhysicsHandleComponent *PhysicsHandle = nullptr;

	UInputComponent *InputComponent = nullptr;

	//Ray-cast and grab what´s in reach. / Hace el rayo y coge lo que este a su alcance.
	void Grab();

	//Called when Grab is released /  Funcion para cuando se suelta el comando Grab.
	void Released();

	//Find (asuumed) attached phyisics handle
	void FindPhysicsComponent();

	//Setup (asuumed) attached input component
	void SetupInputComponent();

	const FHitResult GetFirstPhysicsBodyInReach();
};
