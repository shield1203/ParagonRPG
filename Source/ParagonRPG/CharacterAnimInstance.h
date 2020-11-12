#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SkillActorBase.h"
#include "CharacterAnimInstance.generated.h"

DECLARE_DELEGATE(FOnAttackHitCheckDelegate);
DECLARE_DELEGATE_OneParam(FOnSkillDelegate, ESkillActorType);

UCLASS()
class PARAGONRPG_API UCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	UPROPERTY()
	bool m_isAttacking;

	UPROPERTY()
	bool m_isComboAttack;

	UPROPERTY()
	bool m_isSkilling;

	UPROPERTY()
	bool m_isHit;

	UPROPERTY()
	bool m_isDeath;

	UPROPERTY()
	uint8 m_attackCount;

	UPROPERTY()
	ESkillActorType m_curSkillType;

	UPROPERTY()
	TArray<UAnimMontage*> m_attackMontage;

	UPROPERTY()
	TMap<ESkillActorType, UAnimMontage*> m_skillMontage;

	UPROPERTY()
	TArray<UAnimMontage*> m_hitMontage;

	UPROPERTY()
	UAnimMontage* m_deathMontage;
public:
	FOnAttackHitCheckDelegate OnAttackHitCheck;
	FOnSkillDelegate OnSkill;

public:
	UCharacterAnimInstance();

	bool CanAction();

	bool IsDeath();

	// Attack
	UFUNCTION(BlueprintCallable)
	void StartAttack();

	UFUNCTION(BlueprintCallable)
	void StopAttack();

	UFUNCTION(BlueprintCallable)
	void AnimNotify_NextAttack();

	UFUNCTION(BlueprintCallable)
	void AnimNotify_AttackHitCheck();

	UFUNCTION(BlueprintCallable)
	void AnimNotify_EndAttack();

	// Skill
	UFUNCTION(BlueprintCallable)
	void StartSkill(ESkillActorType skillType);

	UFUNCTION(BlueprintCallable)
	void AnimNotify_OnSkill();

	UFUNCTION(BlueprintCallable)
	void AnimNotify_EndSkill();

	// Hit
	UFUNCTION(BlueprintCallable)
	void StartHit();

	UFUNCTION(BlueprintCallable)
	void AnimNotify_EndHit();

	// GameOver
	UFUNCTION(BlueprintCallable)
	void StartDeath();
};