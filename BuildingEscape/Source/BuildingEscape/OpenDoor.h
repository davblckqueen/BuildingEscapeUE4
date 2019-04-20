// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvents);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)
	FDoorEvents OnOpen;

	UPROPERTY(BlueprintAssignable)
	FDoorEvents OnClose;

private:
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PreassurePlate = nullptr;
	
	UPROPERTY(EditAnywhere)
	float TriggerMass = 35.f;

	//The owning door
	AActor* Owner = nullptr;

	//Returns total mass in kilograms
	float GetTotalMassOfActorsOnPlate();
};
