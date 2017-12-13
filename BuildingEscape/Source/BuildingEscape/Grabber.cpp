// Copyright Ursa Entertainment

#include "Grabber.h"
#include "Engine/World.h"
#include "CoreMinimal.h"
#include "Gameframework/Actor.h"

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

	// ..., *ObjectName, *ObjectPos)
	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting"));
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	//Get player viewpoint
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint
	(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);
	FString OutLogViewPoint = PlayerViewPointLocation.ToString();
	FString OutLogRotator = PlayerViewPointRotation.ToString();
	UE_LOG(LogTemp, Warning, TEXT("ViewPoint is at %s %s"), *OutLogViewPoint, *OutLogRotator);

	//Rayy-cast out to reach distance

	//See what we hit
}
