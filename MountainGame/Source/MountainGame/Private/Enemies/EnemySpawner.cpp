// Code and content owned and created by Dark Shark Games.

#include "EnemySpawner.h"
#include "EnemyBase.h"
#include "Engine/TriggerBox.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{

}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(SpawnHandle, this, &AEnemySpawner::SpawnEnemy, fTimeToSpawn, false);
}

void AEnemySpawner::SetSpawnAreas(TArray<ATriggerBox*> AreasToSet)
{
	SpawnAreas = AreasToSet;
}

void AEnemySpawner::SpawnEnemy()
{
	if (EnemiesToSpawn.Num() != 0)
	{
		int32 iEnemyIndex = FMath::RandRange(0, EnemiesToSpawn.Num() - 1);

		if (EnemiesToSpawn[iEnemyIndex])
		{
			AEnemyBase* CurEnemy = GetWorld()->SpawnActor<AEnemyBase>(EnemiesToSpawn[iEnemyIndex], GetSpawnLocation(), GetActorRotation());

			UE_LOG(LogTemp, Warning, TEXT("Spawning an enemy!"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("EnemiesToSpawn Contains Invalid Index!"));
		}
		
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Enemies to Spawn"));
	}

	GetWorld()->GetTimerManager().SetTimer(SpawnHandle, this, &AEnemySpawner::SpawnEnemy, fTimeToSpawn, false);
}

FVector AEnemySpawner::GetSpawnLocation()
{
	if (SpawnAreas.Num() != 0)
	{
		int32 iVolumeIndex = FMath::RandRange(0, EnemiesToSpawn.Num() - 1);

		if (SpawnAreas[iVolumeIndex])
		{
			FBox SpawnArea = SpawnAreas[iVolumeIndex]->GetComponentsBoundingBox();
			FVector SpawnLoc = FMath::RandPointInBox(SpawnArea);
			
			return SpawnLoc;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("SpawnAreas Contains Invalid Index!"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Spawn Areas Set"));
	}

	return FVector(0,0,0);
}

