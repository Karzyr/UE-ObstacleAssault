// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	UE_LOG(LogTemp, Display, TEXT("Configured Move Distance: %f"), MoveDistance);
	
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);

}

void AMovingPlatform::MovePlatform(float DeltaTime)
{
		if (ReturnPlatform()) 
		{
			StartLocation += (PlatformVelocity.GetSafeNormal() * MoveDistance);
			SetActorLocation(StartLocation);
			PlatformVelocity = -PlatformVelocity;
		} 
		else 
		{
			FVector CurrentLocation = GetActorLocation();
			CurrentLocation += PlatformVelocity * DeltaTime;
			SetActorLocation(CurrentLocation);
		}
}

bool AMovingPlatform::ReturnPlatform() const
{
	return GetDistanceMoved() > MoveDistance;
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	AddActorLocalRotation(RotationVelocity * DeltaTime);
}

float AMovingPlatform::GetDistanceMoved() const
{
	return FVector::Dist(StartLocation, GetActorLocation());
}