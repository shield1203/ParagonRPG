#include "ParagonRPGGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"

AParagonRPGGameModeBase::AParagonRPGGameModeBase()
{	
	m_audioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("GameModeAudioComponent"));
	m_audioComponent->bAutoActivate = false;
}

void AParagonRPGGameModeBase::StartPlay()
{
	Super::StartPlay();
}

void AParagonRPGGameModeBase::AddWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (nullptr != NewWidgetClass)
	{
		UUserWidget* pAddWidget = CreateWidget(GetWorld(), NewWidgetClass);
		if (pAddWidget)
		{
			pAddWidget->AddToViewport();
			m_Widgets.Add(pAddWidget);
		}
	}
}

UUserWidget* AParagonRPGGameModeBase::GetLastWidget() const
{
	return (m_Widgets.Num() > 0) ? m_Widgets.Last() : nullptr;
}

void AParagonRPGGameModeBase::RemoveLastWidget()
{
	if (m_Widgets.Num() <= 0) return;
	
	m_Widgets[m_Widgets.Num() - 1]->RemoveFromParent();
	m_Widgets.RemoveAt(m_Widgets.Num() - 1);
}

int32 AParagonRPGGameModeBase::GetWidgetsNum() const
{
	return m_Widgets.Num();
}

void AParagonRPGGameModeBase::PlayBGM()
{
	if (nullptr != m_BGM)
	{
		m_audioComponent->Play();
	}
}

void AParagonRPGGameModeBase::StopBGM()
{
	if (m_audioComponent->IsPlaying())
	{
		m_audioComponent->Stop();
	}
}