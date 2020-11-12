#include "ParagonRPGPlayerController.h"
#include "ParagonRPGGameInstance.h"

AParagonRPGPlayerController::AParagonRPGPlayerController()
{
	bShowMouseCursor = true;


}

void AParagonRPGPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UWorld* pWorld = GetWorld();
	UParagonRPGGameInstance* pGameInstance = pWorld ? pWorld->GetGameInstance<UParagonRPGGameInstance>() : nullptr;
	
	if (!pGameInstance)
	{
		return;
	}

	switch (pGameInstance->GetCurGameStep())
	{
	case EGameStep::GameStep_Title: SetVirtualJoystickVisibility(false);
		break;
	case EGameStep::GameStep_Village: SetVirtualJoystickVisibility(true);
		break;
	case EGameStep::GameStep_Dungeon:
		break;
	}
}

void AParagonRPGPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}