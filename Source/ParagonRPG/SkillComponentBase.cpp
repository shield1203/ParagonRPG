#include "SkillComponentBase.h"
#include "Engine/Texture2D.h"
#include "UObject/ConstructorHelpers.h"
#include "ParagonRPGGameInstance.h"

USkillComponentBase::USkillComponentBase()
{
	PrimaryComponentTick.bCanEverTick = false;
}

//void USkillComponentBase::BeginPlay()
//{
//	Super::BeginPlay();
//}

//void USkillComponentBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//}

void USkillComponentBase::Execute(ESkillActorType skillType)
{
	if (!m_skillData.Contains(skillType)) return;
}

void USkillComponentBase::AddSkillData(ESkillActorType skillType)
{
	FSkillData addData;

	UWorld* pWorld = GetWorld();

	UParagonRPGGameInstance* pGameInstance = pWorld ? pWorld->GetGameInstance<UParagonRPGGameInstance>() : nullptr;

	FSkillData* pSkillData = pGameInstance->GetDataTable(EGameDataTable::SkillData)->FindRow<FSkillData>(FName(*(FString::FormatAsNumber(static_cast<uint8>(skillType)))), FString(""));

	FSkillData skillData;
	skillData.SkillName = pSkillData->SkillName;
	skillData.Thumbnail = pSkillData->Thumbnail;
	skillData.Description = pSkillData->Description;
	skillData.Damage = pSkillData->Damage;
	skillData.MP = pSkillData->MP;

	m_skillData.Add(skillType, skillData);
}

TMap<ESkillActorType, FSkillData> USkillComponentBase::GetSkillData() const
{
	return m_skillData;
}

bool USkillComponentBase::CanExecute(ESkillActorType skillType, float& curMP)
{
	if (m_skillData.Contains(skillType) && m_skillData[skillType].MP <= curMP)
	{
		curMP -= m_skillData[skillType].MP;

		return true;
	}

	return false;
}

UTexture2D* USkillComponentBase::GetThumbnail(ESkillActorType skillType) const
{
	UTexture2D* Thumbnail = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *m_skillData[skillType].Thumbnail));
	return Thumbnail;
}