// Code and content owned and created by Dark Shark Games.

#include "LightningBall.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "EnemyBase.h"

ALightningBall::ALightningBall()
{
	BookComponent = FindComponentByClass<UPaperFlipbookComponent>();

	BookComponent->OnComponentBeginOverlap.AddDynamic(this, &ALightningBall::OnOverlapBegin);
}

void ALightningBall::SetLifeSpan(float InValue)
{
	MyStats.fLifeSpan = InValue;
}

void ALightningBall::SetDamage(float InValue)
{
	MyStats.fDamage = InValue;
}

void ALightningBall::BeginPlay()
{
	GetWorld()->GetTimerManager().SetTimer(LifeHandle, this, &ALightningBall::Disipate, MyStats.fLifeSpan, false);

	UE_LOG(LogTemp, Warning, TEXT("Spawning"));
}

void ALightningBall::Disipate()
{
	Destroy();
}

void ALightningBall::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AEnemyBase* Enemy = Cast<AEnemyBase>(OtherActor);

	if (Enemy)
	{
		Enemy->Damaged(MyStats.fDamage);
	}
}


