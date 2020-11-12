#include "VillageGameMode.h"
#include "ParagonRPGGameInstance.h"
#include "ParagonRPGPlayerController.h"
#include "ParagonRPGCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"

AVillageGameMode::AVillageGameMode()
{
	UWorld* pWorld = GetWorld();
	UParagonRPGGameInstance* pGameInstance = pWorld ? pWorld->GetGameInstance<UParagonRPGGameInstance>() : nullptr;

	if (!pGameInstance)
	{
		return;
	}
	pGameInstance->SetCurGameStep(EGameStep::GameStep_Village);

	PlayerControllerClass = AParagonRPGPlayerController::StaticClass();
	
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> MainwidgetClass(TEXT("/Game/Blueprints/WidgetBP/HUD/WB_VillageHUD"));
	if (MainwidgetClass.Succeeded())
	{
		AddWidget(MainwidgetClass.Class);
	}

	static ConstructorHelpers::FObjectFinder<USoundCue> VillageBGM(TEXT("SoundCue'/Game/Sound/VillageBGM_Cue.VillageBGM_Cue'"));
	if (VillageBGM.Succeeded())
	{
		m_BGM = VillageBGM.Object;
	}

	m_audioComponent->SetSound(m_BGM);
	PlayBGM();
}