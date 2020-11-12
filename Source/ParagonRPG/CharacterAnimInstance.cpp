#include "CharacterAnimInstance.h"
#include "UObject/ConstructorHelpers.h"
#include "ParagonRPGCharacter.h"

UCharacterAnimInstance::UCharacterAnimInstance()
{
	m_isAttacking = false;
	m_isComboAttack = false;
	m_isSkilling = false;
	m_isHit = false;
	m_isDeath = false;
	m_attackCount = 0;

	// AttackMontage Load
	ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE0(TEXT("AnimMontage'/Game/Animations/Attack_A_Montage.Attack_A_Montage'"));
	if (ATTACK_MONTAGE0.Succeeded())
	{
		m_attackMontage.Add(ATTACK_MONTAGE0.Object);
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE1(TEXT("AnimMontage'/Game/Animations/Attack_B_Montage.Attack_B_Montage'"));
	if (ATTACK_MONTAGE1.Succeeded())
	{
		m_attackMontage.Add(ATTACK_MONTAGE1.Object);
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE2(TEXT("AnimMontage'/Game/Animations/Attack_C_Montage.Attack_C_Montage'"));
	if (ATTACK_MONTAGE2.Succeeded())
	{
		m_attackMontage.Add(ATTACK_MONTAGE2.Object);
	}

	// SkillMontage Load
	ConstructorHelpers::FObjectFinder<UAnimMontage> SKILL_MONTAGE0(TEXT("AnimMontage'/Game/Animations/Skill_A_Montage.Skill_A_Montage'"));
	if (SKILL_MONTAGE0.Succeeded())
	{
		m_skillMontage.Add(ESkillActorType::IceExplosion, SKILL_MONTAGE0.Object);
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> SKILL_MONTAGE1(TEXT("AnimMontage'/Game/Animations/Skill_B_Montage.Skill_B_Montage'"));
	if (SKILL_MONTAGE1.Succeeded())
	{
		m_skillMontage.Add(ESkillActorType::IceBall, SKILL_MONTAGE1.Object);
	}

	// HitMontage Load
	ConstructorHelpers::FObjectFinder<UAnimMontage> Hit_MONTAGE0(TEXT("AnimMontage'/Game/Animations/HitReact_Back_Montage.HitReact_Back_Montage'"));
	if (Hit_MONTAGE0.Succeeded())
	{
		m_hitMontage.Add(Hit_MONTAGE0.Object);
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> Hit_MONTAGE1(TEXT("AnimMontage'/Game/Animations/HitReact_Front_Montage.HitReact_Front_Montage'"));
	if (Hit_MONTAGE1.Succeeded())
	{
		m_hitMontage.Add(Hit_MONTAGE1.Object);
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> Hit_MONTAGE2(TEXT("AnimMontage'/Game/Animations/HitReact_Left_Montage.HitReact_Left_Montage'"));
	if (Hit_MONTAGE2.Succeeded())
	{
		m_hitMontage.Add(Hit_MONTAGE2.Object);
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> Hit_MONTAGE3(TEXT("AnimMontage'/Game/Animations/HitReact_Right_Montage.HitReact_Right_Montage'"));
	if (Hit_MONTAGE3.Succeeded())
	{
		m_hitMontage.Add(Hit_MONTAGE3.Object);
	}

	// GameOver
	ConstructorHelpers::FObjectFinder<UAnimMontage> Death_MONTAGE(TEXT("AnimMontage'/Game/Animations/Death_Montage.Death_Montage'"));
	if (Death_MONTAGE.Succeeded())
	{
		m_deathMontage = Death_MONTAGE.Object;
	}
}

bool UCharacterAnimInstance::CanAction()
{
	return (!m_isSkilling && !m_isHit && !m_isDeath);
}

bool UCharacterAnimInstance::IsDeath()
{
	return m_isDeath;
}

void UCharacterAnimInstance::StartAttack()
{
	if (m_isSkilling || m_isDeath) return;

	m_isAttacking = true;

	if (!m_isComboAttack && m_attackMontage.IsValidIndex(m_attackCount))
	{
		Montage_Play(m_attackMontage[m_attackCount], 1.0f);
		m_isComboAttack = true;
	}
}

void UCharacterAnimInstance::StopAttack()
{
	m_isAttacking = false;
}

void UCharacterAnimInstance::AnimNotify_NextAttack()
{
	if (!m_isAttacking) return;

	m_isComboAttack = true;
	m_attackCount++;
	m_attackCount %= m_attackMontage.Num();
	
	Montage_Play(m_attackMontage[m_attackCount], 1.0f);
}

void UCharacterAnimInstance::AnimNotify_AttackHitCheck()
{
	OnAttackHitCheck.ExecuteIfBound();
}

void UCharacterAnimInstance::AnimNotify_EndAttack()
{
	m_isAttacking = false;
	m_isComboAttack = false;
	m_attackCount = 0;
}

void UCharacterAnimInstance::StartSkill(ESkillActorType skillType)
{
	if (!m_skillMontage.Contains(skillType) || m_isDeath) return;

	m_isSkilling = true;
	m_isAttacking = false;
	m_isComboAttack = false;
	m_isHit = false;
	m_attackCount = 0;

	m_curSkillType = skillType;
	Montage_Play(m_skillMontage[skillType], 1.0f);
}

void UCharacterAnimInstance::AnimNotify_OnSkill()
{
	OnSkill.ExecuteIfBound(m_curSkillType);
}

void UCharacterAnimInstance::AnimNotify_EndSkill()
{
	m_isSkilling = false;
}

void UCharacterAnimInstance::StartHit()
{
	if (m_isAttacking) return;

	int32 nIndex = FMath::RandRange(0, m_hitMontage.Num() - 1);
	if (m_hitMontage.IsValidIndex(nIndex))
	{
		m_isHit = true;
		Montage_Play(m_hitMontage[nIndex], 1.0f);
	}
}

void UCharacterAnimInstance::AnimNotify_EndHit()
{
	m_isHit = false;
}

void UCharacterAnimInstance::StartDeath()
{
	m_isDeath = true;
	Montage_Play(m_deathMontage, 1.0f);
}