#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelTransferVolume.generated.h"

UCLASS()
class PARAGONRPG_API ALevelTransferVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	ALevelTransferVolume();

protected:
	// Called when the game starts or when spawned
	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	FName TransferLevelName;

	UPROPERTY()
	class UBoxComponent* TransferVolume;
};
