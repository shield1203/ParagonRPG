#include "IceBall.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "TimerManager.h"

AIceBall::AIceBall()
{
	m_type = ESkillActorType::IceBall;
	m_speed = 15.5;
	if (!Initialize(m_type)) return;

	m_sceneCompoent = CreateDefaultSubobject<USceneComponent>(TEXT("IceBallSceneComponent"));
	RootComponent = m_sceneCompoent;

	m_particleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("IceBallParticleSystemComponet"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> IceBallParticleAsset(*m_skillData.Particle);
	if (IceBallParticleAsset.Succeeded())
	{
		m_particleComponent->SetTemplate(IceBallParticleAsset.Object);
		UE_LOG(LogTemp, Warning, TEXT("Create Particle : %s"), *m_skillData.Particle);
	}
	m_particleComponent->SetupAttachment(RootComponent);
	m_particleComponent->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));

	m_collisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("IceBallCollisionComponent"));
	m_collisionComponent->InitSphereRadius(m_skillData.Range);
	m_collisionComponent->SetupAttachment(m_particleComponent);

	InitialLifeSpan = 4.1f;
}

void AIceBall::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(m_hitCheckTimerHadle, this, &AIceBall::HitCheck, 0.5f, true);
}

void AIceBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_particleComponent->AddRelativeLocation(FVector(m_speed, 0.0f, 0.0f));
}

void AIceBall::HitCheck()
{
	TArray<FHitResult> HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	//bool bResult = GetWorld()->SweepMultiByChannel(HitResult, GetActorLocation(), GetActorLocation() + GetActorForwardVector() * 200.0f, FQuat::Identity, ECollisionChannel::, FCollisionShape::MakeSphere(m_skillData.Range));
}