#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ParagonRPGPlayerController.generated.h"

UCLASS()
class PARAGONRPG_API AParagonRPGPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:

public:
	AParagonRPGPlayerController();

	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;
};
