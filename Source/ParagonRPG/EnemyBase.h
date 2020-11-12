#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"

USTRUCT(BlueprintType)
struct FEnemyData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString EnemyName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Power;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHP;
};

UCLASS(BlueprintType)
class PARAGONRPG_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

private:
	FEnemyData m_enemyData;

	class UAIPerceptionStimuliSourceComponent* stimulus;

	class UEnemyAnimInstance* m_enemyAnimInstance;

	float m_power;

	float m_curHP;

	float m_maxHP;

protected:
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	void setup_stimulus();
public:	
	AEnemyBase();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	float GetCurHP() const;

	UFUNCTION(BlueprintCallable)
	void Attack();

	UFUNCTION(BlueprintCallable)
	void AttackHitCheck();

	UFUNCTION(BlueprintCallable)
	bool IsAttacking() const;

	UFUNCTION(BlueprintCallable)
	bool IsDeath() const;

	UFUNCTION(BlueprintCallable)
	void Hit();

	UFUNCTION(BlueprintCallable)
	void Death();
};
