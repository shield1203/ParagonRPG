#include "BTTask_Attack.h"
#include "EnemyAIController.h"
#include "EnemyBase.h"
#include "Blackboard_Keys.h"

UBTTask_Attack::UBTTask_Attack(FObjectInitializer const& object_initializer)
{
    bNotifyTick = true;
    NodeName = TEXT("Melee Attack");
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AEnemyAIController* const cont = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
    AEnemyBase* const enemy = Cast<AEnemyBase>(cont->GetPawn());
    enemy->Attack();

    m_isExecute = true;

    return EBTNodeResult::InProgress;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    AEnemyAIController* const cont = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
    AEnemyBase* const enemy = Cast<AEnemyBase>(cont->GetPawn());

    if (m_isExecute && !enemy->IsAttacking())
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    }
    else if (enemy->IsDeath())
    {
        FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
    }
}