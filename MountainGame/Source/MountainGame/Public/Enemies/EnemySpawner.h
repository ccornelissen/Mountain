// Code and content owned and created by Dark Shark Games.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

class AEnemyBase;
class ATriggerBox;

UCLASS()
class MOUNTAINGAME_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

	void SetSpawnAreas(TArray<ATriggerBox*> AreasToSet);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void SpawnEnemy();
	FVector GetSpawnLocation();

	FTimerHandle SpawnHandle;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	float fTimeToSpawn = 2.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TArray<TSubclassOf<AEnemyBase>> EnemiesToSpawn;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	TArray<ATriggerBox*> SpawnAreas;
	
	
};
