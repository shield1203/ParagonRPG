#include "CharacterSkillComponent.h"
#include "EnergyBall.h"
#include "IceBall.h"

UCharacterSkillComponent::UCharacterSkillComponent()
{
}

void UCharacterSkillComponent::Initialize()
{
	AddSkillData(ESkillActorType::IceExplosion);
	AddSkillData(ESkillActorType::IceBall);
}

void UCharacterSkillComponent::Execute(ESkillActorType skillType)
{
	Super::Execute(skillType);

	switch (skillType)
	{
	case ESkillActorType::IceExplosion: Explosion();
		break;
	case ESkillActorType::IceBall: IceBall();
		break;
	}
}

void UCharacterSkillComponent::Explosion()
{
	
}

void UCharacterSkillComponent::IceBall()
{
	UWorld* pWorld = GetWorld();
	if (pWorld)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = GetOwner();
		FVector  SpawnLocation;
		FRotator rotator;
		GetOwner()->GetActorEyesViewPoint(SpawnLocation, rotator);
		SpawnLocation = GetOwner()->GetActorLocation();
		rotator.Pitch = 0.0f;

		AIceBall* pEnergyBall = pWorld->SpawnActor<AIceBall>(AIceBall::StaticClass(), SpawnLocation, rotator, SpawnParams);
	}
}