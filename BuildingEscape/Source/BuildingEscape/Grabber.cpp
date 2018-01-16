// Copyright Ursa Entertainment

#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "components/InputComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

#include "Classes/Components/BoxComponent.h"

#define OUT
// Sets default values for this component's properties
UGrabber::UGrabber()
{
	PrimaryComponentTick.bCanEverTick = true; 	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features off to improve performance if you don't need them.
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandleComponent();
	SetupInputCompenent();
} 

//Check iff physics handle is attached
void UGrabber::FindPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>(); //find physicshandler
	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing physics handle component"), *GetOwner()->GetName());
	}
}

//Check iff inputcomponent is attached
void UGrabber::SetupInputCompenent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
		
	if (InputComponent)
	{
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
	// try and reach any actors with physics body collision channel set
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();

	if (ActorHit) 		// if we hit something then attach a physics handle
{

PhysicsHandle->GrabComponent		//Attach physics handle
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
	PhysicsHandle->ReleaseComponent();
}

void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
		
	if (PhysicsHandle->GrabbedComponent) //if the physics handle is attached
	{
		PhysicsHandle->SetTargetLocation
		(
			GetPlayerReachLineEnd()
		);
	} 
		
	GetFirstPhysicsBodyInReach(); 
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{

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
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner()); // setup query parameters

	FHitResult HitResult; //Ray-cast/line trace out to reach distance
}

/*	GetWorld()->LineTraceSingleByObjectType
	(
		OUT Hit,
		GetPlayerReachLineStart(),
		GetPlayerReachLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	); //See what we hit
	
	AActor* ActorHit = Hit.GetActor(); //get actor returns a "pointer" (*) so aactor most have a *
		*/
/*if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("You hit %s"), *(ActorHit->GetName())); //Dereference the pointer by using *
	} 
	return Hit;
} */

FVector GetPlayerReachLineStart();
{
	FVector PlayerViewPointLocation; 	//Get player viewpoint
	FRotator PlayerViewPointRotation; 	//Get player rotation

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint
	(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	return PlayerViewPointLocation; 	//Start off viewpoint aka start of reach line
}

FVector GetPlayerReachLineEnd();
{
FVector PlayerViewPointLocation; 	//Get player viewpoint
FRotator PlayerViewPointRotation; 	//Get player rotation

GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint
(
	OUT PlayerViewPointLocation,
	OUT PlayerViewPointRotation
);

return UGrabber::LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach; 	//Line in front of pawn -to use for grabber
}

