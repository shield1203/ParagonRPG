#include "NPCCharacterBase.h"
#include "Engine/Classes/Components/SceneComponent.h"
#include "Engine/Classes/Components/BoxComponent.h"
#include "Engine/Classes/Components/SkeletalMeshComponent.h"
#include "Blueprint/UserWidget.h"

// Sets default values
ANPCCharacterBase::ANPCCharacterBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	CollisionVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionVolume"));;
	CollisionVolume->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
	CollisionVolume->SetupAttachment(RootComponent);

	NPCVisual = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("NPCMesh"));
	NPCVisual->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ANPCCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ANPCCharacterBase::VisibleButtonWidget(bool visibleValue)
{
	if (m_ButtonWidgetClass == nullptr) return;

	if (visibleValue && m_buttonWidget == nullptr)
	{
		m_buttonWidget = CreateWidget(GetWorld(), m_ButtonWidgetClass);
		m_buttonWidget->AddToViewport();
	}
	else if(m_buttonWidget != nullptr)
	{
		m_buttonWidget->RemoveFromViewport();
		m_buttonWidget = nullptr;
	}
}

// Called every frame
//void ANPCCharacterBase::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

