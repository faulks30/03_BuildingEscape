// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

//    Owner = GetOwner();
}

float UOpenDoor::WeightOnPressurePlate()
{
    float TotalMass = 0.f;
    TArray<AActor*>OverlappingActors;
    PressurePlate->GetOverlappingActors(OUT OverlappingActors);
    
    for (const auto& Actor : OverlappingActors)
    {
        TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
    }
    return TotalMass;
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (WeightOnPressurePlate() > TriggerWeight) {
        OnOpen.Broadcast();
    } else {
        OnClose.Broadcast();
    }
}

