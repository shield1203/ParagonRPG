#include "TitleGameMode.h"
#include "ParagonRPGGameInstance.h"
#include "ParagonRPGPlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

ATitleGameMode::ATitleGameMode()
{
	UWorld* pWorld = GetWorld();
	UParagonRPGGameInstance* pGameInstance = pWorld ? pWorld->GetGameInstance<UParagonRPGGameInstance>() : nullptr;

	if (!pGameInstance)
	{
		return;
	}
	pGameInstance->SetCurGameStep(EGameStep::GameStep_Title);

	PlayerControllerClass = AParagonRPGPlayerController::StaticClass();

	static ConstructorHelpers::FClassFinder<UUserWidget> MainwidgetClass(TEXT("/Game/Blueprints/WidgetBP/Title/WB_TitleWidget"));
	if (MainwidgetClass.Succeeded())
	{
		AddWidget(MainwidgetClass.Class);
	}
}