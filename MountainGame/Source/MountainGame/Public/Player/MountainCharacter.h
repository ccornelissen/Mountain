// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MountainCharacter.generated.h"


UENUM()
enum class EPlayerStates : uint8
{
	PS_Idle,
	PS_Casting,
	PS_Invulnerable,
	PS_Max
};

UENUM()
enum class EPlayerUltimate : uint8
{
	PU_Storm,
	PU_StaticWall,
	PU_QuickCharge, // 50% charge rate
	PU_WhiteLightning, //Double Damage
	PU_HumidAir, //Double Ball life
	PU_Max
};

USTRUCT(BlueprintType)
struct FPlayerVariables
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	float fPlayerChargeTime = 1.5f;

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	float fPlayerHealth = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	float fUltimateCastTime = 3.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	float fDamage = 50.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	float fBallLifeSpan = 1.5f;
};

class UCameraComponent;
class USpringArmComponent;
class UPaperFlipbookComponent;
class UPaperFlipbook;
class ALightningBall;

UCLASS()
class MOUNTAINGAME_API AMountainCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	/** For rendering the 2D character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UPaperFlipbookComponent* BookComponent;

public:
	// Sets default values for this character's properties
	AMountainCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	/** Returns CameraBoom subobject **/
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	FORCEINLINE UPaperFlipbookComponent* GetBookComponent() const { return BookComponent; }

	void Damaged(float InDamage);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	void Attack(FVector SpawnLocation);

	void GameOver();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, Category = "States")
	EPlayerStates CurrentPlayerState = EPlayerStates::PS_Idle;

	UPROPERTY(EditDefaultsOnly, Category = "States")
	EPlayerUltimate CurrentUltimate = EPlayerUltimate::PU_Storm;

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	FPlayerVariables MyStats;

	UPROPERTY(EditDefaultsOnly, Category = "Ranged")
	TSubclassOf<ALightningBall> LightningBall = nullptr;

private:
	FTimerHandle ChargeHandle;

	FRotator SpawnRotation = FRotator(0.0f, 0.0f, -90.0f);

	bool bCharging;

	FVector SpawnLocation = FVector(0, 0, 0);

	void PlayerCharged();
};
