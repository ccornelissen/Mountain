// Code and content owned and created by Dark Shark Games.

#include "EnemyBase.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "MountainCharacter.h"


// Sets default values
AEnemyBase::AEnemyBase()
{
	BookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("BookComponent"));
	BookComponent->SetupAttachment(RootComponent);
	BookComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBase::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnemyBase::Attack()
{
}

void AEnemyBase::Move()
{
}

void AEnemyBase::IncreaseSize()
{
}

void AEnemyBase::Damaged(float InDamage)
{
	MyStats.fEnemyHealth = MyStats.fEnemyHealth - InDamage;

	if (MyStats.fEnemyHealth <= 0)
	{
		Death();
	}

}

void AEnemyBase::Death()
{
	UE_LOG(LogTemp, Warning, TEXT("I Died :( "));
	Destroy();
}

void AEnemyBase::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AMountainCharacter* HitCharacter = Cast<AMountainCharacter>(OtherActor);

	if (HitCharacter && bCanAttack)
	{
		HitCharacter->Damaged(MyStats.fEnemyDamage);
		bCanAttack = false;
	}
}

