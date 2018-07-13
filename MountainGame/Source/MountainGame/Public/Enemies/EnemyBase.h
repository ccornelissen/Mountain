// Code and content owned and created by Dark Shark Games.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"

UENUM()
enum class EEnemyStates : uint8
{
	ES_Moving,
	ES_Attacking,
	ES_Dying,
	ES_Max
};

USTRUCT(BlueprintType)
struct FEnemyVariables
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	float fEnemyHealth = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	float fEnemyMovementSpeed = 3.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	float fEnemyDamage = 50.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	float fEnemySizeIncrease = 1.5f;
};

class UPaperFlipbookComponent;
class UPaperFlipbook;

UCLASS()
class MOUNTAINGAME_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

	/** For rendering the 2D character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UPaperFlipbookComponent* BookComponent;

public:
	// Sets default values for this character's properties
	AEnemyBase();

	FORCEINLINE UPaperFlipbookComponent* GetBookComponent() const { return BookComponent; }

	void Damaged(float InDamage);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Attack();

	void Move();

	void IncreaseSize();

	void Death();

	UPROPERTY(EditDefaultsOnly, Category = "States")
	EEnemyStates CurrentEnemyState = EEnemyStates::ES_Moving;

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	FEnemyVariables MyStats;

private:
	FTimerHandle DeathHandle;

	bool bCanAttack = true;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
