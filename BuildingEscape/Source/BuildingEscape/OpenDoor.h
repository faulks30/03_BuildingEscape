// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorRequest);

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
    void extracted();
    float WeightOnPressurePlate();

    // Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UPROPERTY(BlueprintAssignable)
    FDoorRequest OnOpen;
    
    UPROPERTY(BlueprintAssignable)
    FDoorRequest OnClose;

private:
//    AActor *Owner;

    UPROPERTY(EditAnywhere)
    float TriggerWeight = 20.0f;
    
    UPROPERTY(EditAnywhere)
    ATriggerVolume *PressurePlate;
};
