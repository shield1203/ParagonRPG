#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Portal.generated.h"

UCLASS()
class PARAGONRPG_API APortal : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Portal", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> m_dungeonListWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Portal", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* m_sceneCompoent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Portal", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* m_collisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Portal", meta = (AllowPrivateAccess = "true"))
	class UParticleSystemComponent* m_particleComponent;
	
protected:
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:	
	APortal();
	virtual void Tick(float DeltaTime) override;

};
