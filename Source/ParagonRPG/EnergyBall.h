#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnergyBall.generated.h"

UCLASS()
class PARAGONRPG_API AEnergyBall : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Projectile")
	class USceneComponent* m_sceneCompoent;

	UPROPERTY(VisibleDefaultsOnly, Category = "Projectile")
	class  USphereComponent* m_collisionComponent;

	UPROPERTY(VisibleAnywhere, Category = "Projectile")
	class UParticleSystemComponent* m_particleComponent;

	virtual void BeginPlay() override;

public:	
	AEnergyBall();

	void SetWay(const FRotator rotation);

	virtual void Tick(float DeltaTime) override;
};
