#include "EnemyBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"
#include "EnemyAnimInstance.h"
#include "EnemyAIController.h"

AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Tags.Add(FName("Enemy"));
	GetCharacterMovement()->bOrientRotationToMovement = true;

	m_power = 60;
	m_maxHP = 400;
	m_curHP = m_maxHP;

	setup_stimulus();
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	m_enemyAnimInstance = Cast<UEnemyAnimInstance>(GetMesh()->GetAnimInstance());
	m_enemyAnimInstance->OnAttackHitCheck_Enemy.BindUFunction(this, FName("AttackHitCheck"));
}

float AEnemyBase::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float fResultDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	
	m_curHP -= fResultDamage;

	if (m_curHP > 0)
	{
		m_enemyAnimInstance->StartHit();
	}
	else
	{
		Death();
		m_enemyAnimInstance->StartDeath();
	}

	return fResultDamage;
}

void AEnemyBase::setup_stimulus()
{
	stimulus = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("stimulus"));
	stimulus->RegisterForSense(TSubclassOf<UAISense_Sight>());
	stimulus->RegisterWithPerceptionSystem();
}

void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AEnemyBase::GetCurHP() const
{
	return (m_curHP / m_maxHP);
}

void AEnemyBase::Attack()
{
	if (!m_enemyAnimInstance->IsDeath())
	{
		m_enemyAnimInstance->StartAttack();
	}
}

void AEnemyBase::AttackHitCheck()
{
	TArray<FHitResult> HitResults;
	FCollisionQueryParams Params(NAME_None, false, this);
	Params.AddIgnoredActor(this);

	bool bResult = GetWorld()->SweepMultiByChannel(HitResults, GetActorLocation(), GetActorLocation() + GetActorForwardVector() * 50.0f,
		FQuat::Identity, ECollisionChannel::ECC_Pawn, FCollisionShape::MakeSphere(150.0f), Params);

	UE_LOG(LogTemp, Warning, TEXT("AttackHitCheck!!"));

	if (bResult)
	{
		for (FHitResult HitResult : HitResults)
		{
			if (HitResult.GetActor()->ActorHasTag("Player"))
			{
				UE_LOG(LogTemp, Warning, TEXT("Is Hit!!"));
				FDamageEvent DamageEvent;
				HitResult.Actor->TakeDamage(60, DamageEvent, GetController(), this);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Is not Hit!! : %s"), *HitResult.Actor->GetFName().ToString());
			}
		}
	}
}

bool AEnemyBase::IsAttacking() const
{
	return m_enemyAnimInstance->IsAttacking();
}

bool AEnemyBase::IsDeath() const
{
	return m_enemyAnimInstance->IsDeath();
}

void AEnemyBase::Hit()
{
	m_enemyAnimInstance->StartHit();
}

void AEnemyBase::Death()
{
	AEnemyAIController* cont = Cast<AEnemyAIController>(GetController());
	cont->StopAI();
	GetCharacterMovement()->SetMovementMode(MOVE_None);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}