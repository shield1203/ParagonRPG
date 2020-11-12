#include "BTTask_TurnToPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "EnemyAIController.h"
#include "EnemyBase.h"
#include "Blackboard_Keys.h"

UBTTask_TurnToPlayer::UBTTask_TurnToPlayer(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Turn To Player");
}

EBTNodeResult::Type UBTTask_TurnToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyAIController* const cont = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	AEnemyBase* const enemy = Cast<AEnemyBase>(cont->GetPawn());
	FVector const player_location = cont->GetBlackboard()->GetValueAsVector(bb_keys::target_location);

	FVector LookVector = player_location - enemy->GetActorLocation();
	LookVector.Z = 0.0f;
	FRotator playerRotator = FRotationMatrix::MakeFromX(LookVector).Rotator();
	enemy->SetActorRotation(playerRotator);

	cont->StopMovement();

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}