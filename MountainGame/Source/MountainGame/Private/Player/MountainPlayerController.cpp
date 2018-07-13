// Code and content owned and created by Dark Shark Games.

#include "MountainPlayerController.h"


FVector AMountainPlayerController::GetFingerHitLocation(ETouchIndex::Type InFinger)
{
	FHitResult FingerHit;

	if (GetHitResultUnderFingerByChannel(InFinger, TraceTypeQuery1, true, FingerHit))
	{
		UE_LOG(LogTemp, Warning, TEXT("Returning Click Location"));

		return FingerHit.Location;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Returning Null Instead of Finger Location"));

		return FVector(0,0,0);
	}

}

