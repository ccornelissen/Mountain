// Code and content owned and created by Dark Shark Games.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MountainPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MOUNTAINGAME_API AMountainPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	FVector GetFingerHitLocation(ETouchIndex::Type InFinger);
	
	
	
};
