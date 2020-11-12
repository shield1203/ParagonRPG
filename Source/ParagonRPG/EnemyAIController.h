#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "EnemyAIController.generated.h"

UCLASS(config=Game)
class PARAGONRPG_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTreeComponent* behavior_tree_Comp;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTree* btree;

	class UBlackboardComponent* blackboard;
	class UAISenseConfig_Sight* sight_config;

public:
	class UBlackboardComponent* GetBlackboard() const;

private:
	void setup_perception_system();

public:
	AEnemyAIController(FObjectInitializer const& object_initializer = FObjectInitializer::Get());

	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* Pawn) override;
	virtual void Tick(float DeltaSeconds) override;
	virtual FRotator GetControlRotation() const override;

	UFUNCTION(BlueprintCallable)
	void StopAI();

	UFUNCTION(BlueprintCallable, Category = "Behavior")
	void on_target_detected(AActor* actor, FAIStimulus const stimulus);
};
