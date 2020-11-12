#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimInstance.generated.h"

DECLARE_DELEGATE(FOnAttackHitCheckDelegate_Enemy);

UCLASS(BlueprintType)
class PARAGONRPG_API UEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	bool m_isAttacking = false;
	bool m_isHiting = false;
	bool m_death = false;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Montage", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* m_attackMontage;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Montage", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* m_hitMontage;
	
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Montage", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* m_deathMontage;

public:
	FOnAttackHitCheckDelegate_Enemy OnAttackHitCheck_Enemy;

public:
	UEnemyAnimInstance();

	bool IsAttacking();
	bool IsDeath();
	void StartAttack();
	void StartHit();
	void StartDeath();

	UFUNCTION(BlueprintCallable)
	void AnimNotify_AttackHitCheck();

	UFUNCTION(BlueprintCallable)
	void AnimNotify_EndAttack();

	UFUNCTION(BlueprintCallable)
	void AnimNotify_EndHit();

	UFUNCTION(BlueprintCallable)
	void AnimNotify_EndDeath();
};
