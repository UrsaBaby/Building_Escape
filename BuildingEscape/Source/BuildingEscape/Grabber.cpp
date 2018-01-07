// Copyright Ursa Entertainment

#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "components/InputComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

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
	FindPhysicsHandleComponent();
	SetupInputCompenent();
	
}

void UGrabber::FindPhysicsHandleComponent()
{
	//find physicshandler
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	

}

void UGrabber::SetupInputCompenent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (PhysicsHandle)
	{
		///
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing physics handle component"), *GetOwner()->GetName());
	}
	if (InputComponent)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Inputcomponent found"));
		// bind input action
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing Inputcomponent"), *GetOwner()->GetName());
	}
}

void UGrabber::Grab() 
{
	UE_LOG(LogTemp, Warning, TEXT("Grab Pressed"));

	// try and reach any actors with physics body collision channel set
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ActorHit = HitResult.GetActor();
	auto ComponentToGrab = HitResult.GetComponent();
	

	// if we hit something then attach a physics handle
	if (ActorHit)
	{
		//Attach physics handle
		PhysicsHandle->GrabComponent
		(
			ComponentToGrab,
			NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation(),
			true
		);
	}
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab released"));
	PhysicsHandle->ReleaseComponent();
	//TODO release Physics handle
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//TODO Refactor
	//Get player viewpoint
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint
	(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);


	//draw a red trace to visualise
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;



	// ...
	//if the physics handle is attached
	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation
		(
			LineTraceEnd
		);
	}
		// move object that we are holding


	GetFirstPhysicsBodyInReach();
	
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	//Get player viewpoint
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint
	(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	/*UE_LOG(LogTemp, Warning, TEXT("ViewPoint is at %s %s"), *PlayerViewPointRotation.ToString(), *PlayerViewPointLocation.ToString());*/

	//draw a red trace to visualise
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;


	/*DrawDebugLine
	(
	GetWorld(),
	PlayerViewPointLocation,
	LineTraceEnd,
	FColor(255, 0, 0),
	false,
	0.f,
	0.f,
	10.f
	); */

	// setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());


	//Ray-cast/line trace out to reach distance
	FHitResult Hit;

	GetWorld()->LineTraceSingleByObjectType
	(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);
	//See what we hit
	AActor* ActorHit = Hit.GetActor(); //getactor returns a "pointer" (*) so aactor most have a *

	// see what you hit in log
/*	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("You hit %s"), *(ActorHit->GetName())); //Dereference the pointer by using *
	} */

	return Hit;
}

