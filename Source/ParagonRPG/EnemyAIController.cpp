#include "EnemyAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "UObject/ConstructorHelpers.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "blackboard_keys.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "GameFramework/Character.h"
#include "Engine.h"

#include "ParagonRPGCharacter.h"
#include "EnemyBase.h"

AEnemyAIController::AEnemyAIController(FObjectInitializer const& object_initializer)
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> EnemyBT_obj(TEXT("BehaviorTree'/Game/Blueprints/AI/BT_Enemy.BT_Enemy'"));
	if (EnemyBT_obj.Succeeded())
	{
		btree = EnemyBT_obj.Object;
	}
	behavior_tree_Comp = object_initializer.CreateAbstractDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
	blackboard = object_initializer.CreateAbstractDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));

	setup_perception_system();
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(btree);
	behavior_tree_Comp->StartTree(*btree);
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AEnemyAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

FRotator AEnemyAIController::GetControlRotation() const
{
	if (nullptr == GetPawn())
	{
		return FRotator(0.f, 0.f, 0.f);
	}

	return FRotator(0.f, GetPawn()->GetActorRotation().Yaw, 0.f);
}

void AEnemyAIController::on_target_detected(AActor* actor, FAIStimulus const stimulus)
{
	if (auto const player = Cast<AParagonRPGCharacter>(actor))
	{
		GetBlackboard()->SetValueAsBool(bb_keys::can_see_player, stimulus.WasSuccessfullySensed());
	}
}

UBlackboardComponent* AEnemyAIController::GetBlackboard() const
{
	return blackboard;
}

void AEnemyAIController::StopAI()
{
	auto BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	
	if (nullptr != BehaviorTreeComponent)
	{
		BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
	}
}

void AEnemyAIController::setup_perception_system()
{
	sight_config = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));

	sight_config->SightRadius = 500.0f; // 시야 범위
	sight_config->LoseSightRadius = sight_config->SightRadius; // 시야 밖범위 
	sight_config->PeripheralVisionAngleDegrees = 90; // 시야각
	sight_config->SetMaxAge(5.0f);
	sight_config->AutoSuccessRangeFromLastSeenLocation = 500.f;

	sight_config->DetectionByAffiliation.bDetectEnemies = true;
	sight_config->DetectionByAffiliation.bDetectFriendlies = true;
	sight_config->DetectionByAffiliation.bDetectNeutrals = true;

	GetPerceptionComponent()->SetDominantSense(*sight_config->GetSenseImplementation());
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController::on_target_detected);
	GetPerceptionComponent()->ConfigureSense(*sight_config);
}