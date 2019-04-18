// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
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
    SetupComponents();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (PhysicsHandle->GrabbedComponent)
    {
        PhysicsHandle->SetTargetLocation(GetLineTraceEnd());
    }
}

void UGrabber::Grab()
{
//    UE_LOG(LogTemp, Warning, TEXT("GRABBER PRESSED"))
    auto HitResult = GetFirstPhysicsBodyInReach();
    auto ActorHit = HitResult.GetActor();
    
    if (ActorHit) {
//        UE_LOG(LogTemp, Warning, TEXT("ACTOR GRABBED %s"),*ActorHit->GetName())
        auto ComponentToGrab = HitResult.GetComponent();
        FRotator GrabbedRotation = FRotator(0.0f,0.0f,0.0f);

        PhysicsHandle->GrabComponentAtLocationWithRotation(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation(), GrabbedRotation);
    }
}

void UGrabber::Release()
{
//    UE_LOG(LogTemp, Warning, TEXT("GRABBER RELEASED"))
    PhysicsHandle->ReleaseComponent();
}

void UGrabber::SetupComponents()
{
    PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    if (!PhysicsHandle) {
        UE_LOG(LogTemp, Warning, TEXT("ERROR: No Physics Handle Found"))
    }
    
    InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
    if (!InputComponent) {
        UE_LOG(LogTemp, Warning, TEXT("ERROR: No Input Component Found"))
    } else {
        InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
        InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
    }
}

const FVector UGrabber::GetLineTraceEnd()
{
    FVector PlayerLocation;
    FRotator PlayerRotation;
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerLocation, OUT PlayerRotation);
    
    return PlayerLocation + PlayerRotation.Vector() * Reach;
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
    FVector PlayerLocation;
    FRotator PlayerRotation;
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerLocation, OUT PlayerRotation);
    
    FHitResult HitResult;
    GetWorld()->LineTraceSingleByObjectType(OUT HitResult, PlayerLocation, PlayerLocation + PlayerRotation.Vector() * Reach, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody));
    
    return HitResult;
}

