#include "SkillActorBase.h"
#include "ParagonRPGGameInstance.h"

ASkillActorBase::ASkillActorBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASkillActorBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASkillActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ASkillActorBase::Initialize(ESkillActorType skillType)
{
	UWorld* pWorld = GetWorld();

	UParagonRPGGameInstance* pGameInstance = pWorld ? pWorld->GetGameInstance<UParagonRPGGameInstance>() : nullptr;

	if (!pGameInstance) return false;
	
	FSkillData* pSkillData = pGameInstance->GetDataTable(EGameDataTable::SkillData)->FindRow<FSkillData>(FName(*(FString::FormatAsNumber(static_cast<uint8>(skillType)))), FString(""));

	if (!pSkillData) return false;

	m_skillData.SkillName = pSkillData->SkillName;
	m_skillData.Thumbnail = pSkillData->Thumbnail;
	m_skillData.Description = pSkillData->Description;
	m_skillData.Particle = pSkillData->Particle;
	m_skillData.Range = pSkillData->Range;
	m_skillData.Damage = pSkillData->Damage;
	m_skillData.MP = pSkillData->MP;
	m_skillData.CoolingTime = pSkillData->CoolingTime;

	return true;
}