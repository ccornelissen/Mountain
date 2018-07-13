// Fill out your copyright notice in the Description page of Project Settings.

#include "MountainCharacter.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "LightningBall.h"
#include "MountainPlayerController.h"


// Sets default values
AMountainCharacter::AMountainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	//Create the player body.
	BookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("BookComponent"));
	BookComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMountainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMountainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMountainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AMountainCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Repeat, this, &AMountainCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AMountainCharacter::TouchStopped);

}

void AMountainCharacter::PlayerCharged()
{
	bCharging = false;
}

void AMountainCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	UE_LOG(LogTemp, Warning, TEXT("Player Touched"));

	AMountainPlayerController* MyController = Cast<AMountainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (MyController)
	{
		SpawnLocation = MyController->GetFingerHitLocation(FingerIndex);
	}
}

void AMountainCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	if (bCharging == false)
	{
		Attack(SpawnLocation);
	}
}

void AMountainCharacter::Attack(FVector SpawnLocation)
{
	if (LightningBall)
	{
		ALightningBall* CurProjectile = GetWorld()->SpawnActor<ALightningBall>(LightningBall, SpawnLocation, SpawnRotation);

		CurProjectile->SetDamage(MyStats.fDamage);

		CurProjectile->SetLifeSpan(MyStats.fBallLifeSpan);

		GetWorld()->GetTimerManager().SetTimer(ChargeHandle, this, &AMountainCharacter::PlayerCharged, MyStats.fPlayerChargeTime, false);

		bCharging = true;
	}
}

void AMountainCharacter::Damaged(float InDamage)
{
	MyStats.fPlayerHealth = MyStats.fPlayerHealth - InDamage;

	if (MyStats.fPlayerHealth <= 0)
	{
		GameOver();
	}
}

void AMountainCharacter::GameOver()
{
	//Bring up game over screen and play ad if applicable
}

