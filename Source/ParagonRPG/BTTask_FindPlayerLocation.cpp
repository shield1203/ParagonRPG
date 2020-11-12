#include "BTTask_FindPlayerLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Blackboard_Keys.h"
#include "EnemyAIController.h"
#include "ParagonRPGCharacter.h"

UBTTask_FindPlayerLocation::UBTTask_FindPlayerLocation(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Find Player Location");
}

EBTNodeResult::Type UBTTask_FindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto const cont = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	ACharacter* const pPlayer = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	FVector const player_location = pPlayer->GetActorLocation();
	
	cont->GetBlackboard()->SetValueAsVector(bb_keys::target_location, player_location);	

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
