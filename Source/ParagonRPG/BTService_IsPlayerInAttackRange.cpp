#include "BTService_IsPlayerInAttackRange.h"
#include "EnemyBase.h"
#include "EnemyAIController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blackboard_Keys.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

UBTService_IsPlayerInAttackRange::UBTService_IsPlayerInAttackRange()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Is Player In Attack Range");
}

void UBTService_IsPlayerInAttackRange::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* node_memory)
{
	Super::OnBecomeRelevant(OwnerComp, node_memory);

	AEnemyAIController* const cont = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	AEnemyBase* const enemy = Cast<AEnemyBase>(cont->GetPawn());
	ACharacter* const pPlayer = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	cont->GetBlackboard()->SetValueAsBool(bb_keys::is_in_attackRange, enemy->GetDistanceTo(pPlayer) <= Attack_range);
}
