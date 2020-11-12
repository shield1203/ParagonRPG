#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SkillActorBase.h"
#include "SkillComponentBase.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PARAGONRPG_API USkillComponentBase : public USceneComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly)
	TMap<ESkillActorType, FSkillData> m_skillData;

protected:
	//virtual void BeginPlay() override;

public:	
	USkillComponentBase();

	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void Initialize() {};

	UFUNCTION(BlueprintCallable)
	bool CanExecute(ESkillActorType skillType, float& curMP);

	UFUNCTION(BlueprintCallable)
	virtual void Execute(ESkillActorType skillType);

	void AddSkillData(ESkillActorType skillType);

	UFUNCTION(BlueprintCallable)
	TMap<ESkillActorType, FSkillData> GetSkillData() const;

	UFUNCTION(BlueprintCallable)
	class UTexture2D* GetThumbnail(ESkillActorType skillType) const;
};
