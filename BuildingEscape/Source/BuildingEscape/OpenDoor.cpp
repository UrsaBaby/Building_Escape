// Copyright Ursa Entertainment

#include "OpenDoor.h"
#include "CoreMinimal.h"
#include "Gameframework/Actor.h"
#include "Engine/World.h"

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

	Owner = GetOwner(); 	// Find owning actor
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn(); //actorthatopens is set to to playercontroller->pawn


	// ...
	
}

void UOpenDoor::OpenDoor()
{
	// Create a rotator
	FRotator NewRotation = FRotator(0.0f, OpenAngle, 0.0f);

	//Set door rotation
	Owner->SetActorRotation(NewRotation);
}

void UOpenDoor::CloseDoor()
{
	// Create a rotator
	FRotator NewRotation = FRotator(0.0f, 90.0f, 0.0f);

	//Set door rotation
	Owner->SetActorRotation(NewRotation);
}



// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	// Poll trigge volume every frame
	if (PressurePlate->IsOverlappingActor(ActorThatOpens)) // if ActorThatOpens is in the volume 
	{
		OpenDoor();  // then open door
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay)
	{
		CloseDoor();
	}
	// Check if its time to close the door
}


		
		

