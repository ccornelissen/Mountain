// Code and content owned and created by Dark Shark Games.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookActor.h"
#include "LightningBall.generated.h"


USTRUCT(BlueprintType)
struct FLightningVariables
{
	GENERATED_BODY()

	float fLifeSpan = 1.5f;
	float fDamage = 100.0f;
};

/**
 *  Players spawned Lightning
 */

class UPaperFlipbookComponent;

UCLASS()
class MOUNTAINGAME_API ALightningBall : public APaperFlipbookActor
{
	GENERATED_BODY()
	
public:
	ALightningBall();

	void SetLifeSpan(float InValue);

	void SetDamage(float InValue);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	FLightningVariables MyStats;

	UPaperFlipbookComponent* BookComponent;

	void Disipate();

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	FTimerHandle LifeHandle;

};
