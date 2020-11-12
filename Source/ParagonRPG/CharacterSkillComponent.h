#pragma once

#include "CoreMinimal.h"
#include "SkillComponentBase.h"
#include "CharacterSkillComponent.generated.h"

UCLASS()
class PARAGONRPG_API UCharacterSkillComponent : public USkillComponentBase
{
	GENERATED_BODY()
	
public:
	UCharacterSkillComponent();

	virtual void Initialize() override;

	virtual void Execute(ESkillActorType skillType) override;

	void Explosion();

	void IceBall();
};