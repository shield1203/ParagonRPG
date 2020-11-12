#include "EnemyAnimInstance.h"
#include "UObject/ConstructorHelpers.h"

UEnemyAnimInstance::UEnemyAnimInstance()
{
	ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE(TEXT("AnimMontage'/Game/Animations/Enemy/Swing_Montage.Swing_Montage'"));
	if (ATTACK_MONTAGE.Succeeded())
	{
		m_attackMontage = ATTACK_MONTAGE.Object;
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> HIT_MONTAGE(TEXT("AnimMontage'/Game/Animations/Enemy/Hitreact_Montage.Hitreact_Montage'"));
	if (HIT_MONTAGE.Succeeded())
	{
		m_hitMontage = HIT_MONTAGE.Object;
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> DEATH_MONTAGE(TEXT("AnimMontage'/Game/Animations/Enemy/Death_Montage.Death_Montage'"));
	if (DEATH_MONTAGE.Succeeded())
	{
		m_deathMontage = DEATH_MONTAGE.Object;
	}
}

bool UEnemyAnimInstance::IsAttacking()
{
	return m_isAttacking;
}

bool UEnemyAnimInstance::IsDeath()
{
	return m_death;
}

void UEnemyAnimInstance::StartAttack()
{
	if (m_isHiting || m_death) return;

	m_isAttacking = true;

	Montage_Play(m_attackMontage, 1.0f);
}

void UEnemyAnimInstance::StartHit()
{
	if (!m_isAttacking)
	{
		m_isHiting = true;
		Montage_Play(m_hitMontage, 1.0f);
	}
}

void UEnemyAnimInstance::StartDeath()
{
	if (!m_death)
	{
		m_death = true;
		Montage_Play(m_deathMontage, 1.0f);
	}
}

void UEnemyAnimInstance::AnimNotify_EndAttack()
{
	m_isAttacking = false;
}

void UEnemyAnimInstance::AnimNotify_EndHit()
{
	m_isHiting = false;
}

void UEnemyAnimInstance::AnimNotify_AttackHitCheck()
{
	if (!m_death)
	{
		OnAttackHitCheck_Enemy.ExecuteIfBound();
	}
}

void UEnemyAnimInstance::AnimNotify_EndDeath()
{
	GetOwningActor()->Destroy();
}