// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank/BattleTank.h"
#include "TankPlayerController.h"



void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) {

		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possing a tank"));
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing: %s"),*(ControlledTank->GetName()));

	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{

	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }
	FVector HitLocation;//out prameter
	if (GetSightRayHitLocation(HitLocation)) //Has "side-effect", is going to line trace
	{
	//UE_LOG(LogTemp, Warning, TEXT("Look Direction: %s"), *HitLocation.ToString());
	// TODO Tell controlled tank to aim at this point
	}
}
// Get world location of linetrace through crosshair, true if it hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	

	// "De-project" the screen position of the crosshair to a wolrd direction 
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		UE_LOG(LogTemp, Warning, TEXT("Look Direction: %s"), *LookDirection.ToString());

	}

	// Linetrace along that look direction, and see what we hit (up to a max range)
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation; // To be discarded
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation, 
		LookDirection


	);
}