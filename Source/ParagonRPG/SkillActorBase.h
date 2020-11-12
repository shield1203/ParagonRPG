#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "SkillActorBase.generated.h"

UENUM(BlueprintType)
enum class ESkillActorType : uint8
{
	IceExplosion UMETA(DisplayName = "IceExplosion"),
	IceBall UMETA(DisplayName = "IceBall"),
};

USTRUCT(BlueprintType)
struct FSkillData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SkillName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Thumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Particle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CoolingTime;
};

UCLASS()
class PARAGONRPG_API ASkillActorBase : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "SkillActorBase")
	ESkillActorType m_type;

	UPROPERTY(VisibleDefaultsOnly, Category = "SkillActorBase")
	FSkillData m_skillData;

	UPROPERTY(VisibleDefaultsOnly, Category = "SkillActorBase")
	class USceneComponent* m_sceneCompoent;

	UPROPERTY(VisibleDefaultsOnly, Category = "SkillActorBase")
	class USphereComponent* m_collisionComponent;

	UPROPERTY(VisibleAnywhere, Category = "SkillActorBase")
	class UParticleSystemComponent* m_particleComponent;

	virtual void BeginPlay() override;

public:	
	ASkillActorBase();

	virtual void Tick(float DeltaTime) override;

	bool Initialize(ESkillActorType skillType);

	UFUNCTION(BlueprintCallable)
	virtual void HitCheck() {};
};
