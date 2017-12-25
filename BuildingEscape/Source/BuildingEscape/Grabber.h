// Copyright Ursa Entertainment

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
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
	// how far ahead of the player can we reach in centimeter
	float Reach = 100.f;
	
	
	UPhysicsHandleComponent * PhysicsHandle = nullptr; //creates a physics handler
	
	UInputComponent * InputComponent = nullptr; // create inputcompenent

	void Grab(); // ray cast and grab whats in reach

	void Release(); //realease
};
