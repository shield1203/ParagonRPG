#include "ComboComponent.h"
#include "TimerManager.h"

UComboComponent::UComboComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UComboComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UComboComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

uint8 UComboComponent::GetComboCount() const
{
	return m_comboCount;
}

void UComboComponent::CountingCombo()
{
	m_comboCount += 1;
	m_comboLifeTime = 3;

	OnCountingCombo.Broadcast();

	if (!m_comboCheckTimer.IsValid())
	{
		GetWorld()->GetTimerManager().SetTimer(m_comboCheckTimer, this, &UComboComponent::CheckCombo, 1.0f, true);
	}
}

void UComboComponent::CheckCombo()
{
	m_comboLifeTime--;

	if (m_comboLifeTime <= 0)
	{
		m_comboCount = 0;
		GetWorld()->GetTimerManager().ClearTimer(m_comboCheckTimer);
		ResetCombo();
	}

	UE_LOG(LogTemp, Warning, TEXT("time : %d"), m_comboLifeTime);
}

void UComboComponent::ResetCombo()
{
	m_comboCount = 0;

	OnResetCombo.Broadcast();
}