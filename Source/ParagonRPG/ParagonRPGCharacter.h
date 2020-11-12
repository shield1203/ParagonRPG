#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/DataTable.h"
#include "ParagonRPGCharacter.generated.h"

USTRUCT(BlueprintType)
struct FCharacterData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 Power;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxMP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxExp;
};

UCLASS(config=Game)
class AParagonRPGCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

private:
	UPROPERTY(VisibleAnywhere, Category = "Animation")
	class UCharacterAnimInstance* m_characterAnimInstance;

	UPROPERTY(VisibleAnywhere, Category = "Skill")
	class USkillComponentBase* m_skillComponent;

	UPROPERTY(VisibleAnywhere, Category = "Combo")
	class UComboComponent* m_comboComponent;

	UPROPERTY(VisibleAnywhere, Category = "Ability")
	uint8 m_level;

	UPROPERTY(VisibleAnywhere, Category = "Ability")
	float m_curHP;
	
	UPROPERTY(VisibleAnywhere, Category = "Ability")
	float m_curMP;

	UPROPERTY(VisibleAnywhere, Category = "Ability")
	float m_curExp;

	UPROPERTY(VisibleAnywhere, Category = "Ability")
	FCharacterData m_characterData;

public:
	AParagonRPGCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

protected:
	void LoadCharacterData();

	void MoveForward(float Value);

	void MoveRight(float Value);

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);

	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
public:
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UFUNCTION(BlueprintCallable)
	class UComboComponent* GetComboComponent() const;

	UFUNCTION(BlueprintCallable)
	uint8 GetLevel() const;

	UFUNCTION(BlueprintCallable)
	float GetHP() const;

	UFUNCTION(BlueprintCallable)
	float GetMP() const;

	UFUNCTION(BlueprintCallable)
	float GetCurExp() const;

	UFUNCTION(BlueprintCallable)
	float GetMaxExp() const;

	UFUNCTION(BlueprintCallable)
	uint8 GetComboCount() const;

	UFUNCTION(BlueprintCallable)
	void Attack();

	UFUNCTION(BlueprintCallable)
	void AttackHitCheck();

	UFUNCTION(BlueprintCallable)
	void Skill(ESkillActorType skillType);
};