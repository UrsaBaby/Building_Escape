// Fill out your copyright notice in the Description page of Project Settings.

#include "PositionReporter.h"
#include "Gameframework/Actor.h"


// Sets default values for this component's properties
UPositionReporter::UPositionReporter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	
}


// Called when the game starts
void UPositionReporter::BeginPlay()
{
	Super::BeginPlay();

	// ...
	//GetOwner är en metod för actors. Getowner är en pointer till en actor (vilken som helst) och använd metoden getname som ger namnet i formatet Fstring. Vi skapar en Fstring som tar emot den stringen
	FString ObjectName = GetOwner()->GetName();
	FString ObjectPos = GetOwner()->GetTransform().GetLocation().ToString();
	UE_LOG(LogTemp, Warning, TEXT("%s is at %s"), *ObjectName, *ObjectPos);
}


// Called every frame
void UPositionReporter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

