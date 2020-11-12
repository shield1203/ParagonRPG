#include "EnergyBall.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "UObject/ConstructorHelpers.h"

AEnergyBall::AEnergyBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_sceneCompoent = CreateDefaultSubobject<USceneComponent>(TEXT("SkillSceneComponent"));
	RootComponent = m_sceneCompoent;

	m_particleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SkillParticleSystemComponet"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("ParticleSystem'/Game/AdvancedMagicFX12/particles/P_ky_shot_ice.P_ky_shot_ice'"));
	if (ParticleAsset.Succeeded())
	{
		m_particleComponent->SetTemplate(ParticleAsset.Object);
	}
	m_particleComponent->SetupAttachment(RootComponent);
	m_particleComponent->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));

	m_collisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SkillSphereComponent"));
	m_collisionComponent->InitSphereRadius(45.0f);
	m_collisionComponent->SetRelativeLocation(FVector(0.0f, -30.0f, 0.0f));
	m_collisionComponent->SetupAttachment(m_particleComponent);

	InitialLifeSpan = 3.0f;
}

void AEnergyBall::SetWay(const FRotator rotation)
{
	//
}

// Called when the game starts or when spawned
void AEnergyBall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnergyBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//m_sceneCompoent->AddRelativeLocation(FVector(15.0f, 0.0f, 0.0f));
	m_particleComponent->AddRelativeLocation(FVector(15.0f, 0.0f, 0.0f));
}

