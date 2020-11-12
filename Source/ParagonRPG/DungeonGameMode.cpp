#include "DungeonGameMode.h"
#include "ParagonRPGGameInstance.h"
#include "ParagonRPGPlayerController.h"
#include "ParagonRPGCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"

ADungeonGameMode::ADungeonGameMode()
{
	UWorld* pWorld = GetWorld();
	UParagonRPGGameInstance* pGameInstance = pWorld ? pWorld->GetGameInstance<UParagonRPGGameInstance>() : nullptr;

	if (!pGameInstance)
	{
		return;
	}
	pGameInstance->SetCurGameStep(EGameStep::GameStep_Dungeon);

	PlayerControllerClass = AParagonRPGPlayerController::StaticClass();

	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/ThirdPersonCharacter"));
	if (nullptr != PlayerPawnBPClass.Class)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> MainwidgetClass(TEXT("/Game/Blueprints/WidgetBP/HUD/WB_DungeonHUD"));
	if (MainwidgetClass.Succeeded())
	{
		AddWidget(MainwidgetClass.Class);
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> ComboWidgetClass(TEXT("/Game/Blueprints/WidgetBP/Dungeon/WB_ComboCount"));
	if (ComboWidgetClass.Succeeded())
	{
		AddWidget(ComboWidgetClass.Class);
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> GameClearWidget(TEXT("/Game/Blueprints/WidgetBP/Dungeon/GameClear"));
	if (GameClearWidget.Succeeded())
	{
		m_gameClearWidget = GameClearWidget.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> GameOverWidget(TEXT("/Game/Blueprints/WidgetBP/Dungeon/GameOver"));
	if (GameOverWidget.Succeeded())
	{
		m_gameOverWidget = GameOverWidget.Class;
	}

	static ConstructorHelpers::FObjectFinder<USoundCue> DungeonBGM(TEXT("SoundCue'/Game/Sound/DungeonBGM_Cue.DungeonBGM_Cue'"));
	if (DungeonBGM.Succeeded())
	{
		m_BGM = DungeonBGM.Object;
	}

	m_audioComponent->SetSound(m_BGM);
	PlayBGM();
}

void ADungeonGameMode::StartPlay()
{
	Super::StartPlay();

	m_Widgets[1]->OnInitialized();
}

void ADungeonGameMode::GameClear()
{
	AddWidget(m_gameClearWidget);
}

void ADungeonGameMode::GameOver()
{
	AddWidget(m_gameOverWidget);
}