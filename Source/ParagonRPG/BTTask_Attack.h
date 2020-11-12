#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_Attack.generated.h"

UCLASS(BlueprintType)
class PARAGONRPG_API UBTTask_Attack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

protected:
	bool m_isExecute = false;

public:
	UBTTask_Attack(FObjectInitializer const& object_initializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
