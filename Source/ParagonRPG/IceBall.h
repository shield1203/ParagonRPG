#pragma once

#include "CoreMinimal.h"
#include "SkillActorBase.h"
#include "IceBall.generated.h"

UCLASS()
class PARAGONRPG_API AIceBall : public ASkillActorBase
{
	GENERATED_BODY()
	
private:
	float m_speed;

	FTimerHandle m_hitCheckTimerHadle;

protected:
	virtual void BeginPlay() override;

public:
	AIceBall();

	virtual void Tick(float DeltaTime) override;
	virtual void HitCheck() override;
};
