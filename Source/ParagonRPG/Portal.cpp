#include "Portal.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "ParagonRPGCharacter.h"
#include "ParagonRPGGameModeBase.h"

APortal::APortal()
{
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FClassFinder<UUserWidget> DungeonListWidget(TEXT("/Game/Blueprints/WidgetBP/Village/WB_Portal"));
	if (DungeonListWidget.Succeeded())
	{
		m_dungeonListWidget = DungeonListWidget.Class;
	}

	m_sceneCompoent = CreateDefaultSubobject<USceneComponent>(TEXT("PortalSceneComponent"));
	RootComponent = m_sceneCompoent;

	m_particleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PortalParticleSystemComponet"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> PortalParticleAsset(TEXT("ParticleSystem'/Game/AdvancedMagicFX12/particles/P_ky_aura_ice.P_ky_aura_ice'"));
	if (PortalParticleAsset.Succeeded())
	{
		m_particleComponent->SetTemplate(PortalParticleAsset.Object);
	}
	m_particleComponent->SetupAttachment(RootComponent);
	m_particleComponent->SetRelativeScale3D(FVector(0.75f, 0.75f, 2.5f));

	m_collisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("PortalCollisionComponent"));
	m_collisionComponent->InitSphereRadius(115.0f);
	m_collisionComponent->SetupAttachment(m_particleComponent);
	m_collisionComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 88.0f));
}

void APortal::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void APortal::NotifyActorBeginOverlap(AActor* OtherActor)
{
	AParagonRPGCharacter* pPlayer = Cast<AParagonRPGCharacter>(OtherActor);

	if (nullptr != pPlayer)
	{
		AParagonRPGGameModeBase* pGameMode = Cast<AParagonRPGGameModeBase>(GetWorld()->GetAuthGameMode());
		pGameMode->AddWidget(m_dungeonListWidget);
	}
}

void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

