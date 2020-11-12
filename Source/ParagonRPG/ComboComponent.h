#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ComboComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCountingCombo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnResetCombo);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PARAGONRPG_API UComboComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	uint8 m_comboCount = 0;

	uint8 m_comboLifeTime;

	FTimerHandle m_comboCheckTimer;

public:	
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
	FOnCountingCombo OnCountingCombo;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
	FOnResetCombo OnResetCombo;

protected:
	virtual void BeginPlay() override;

public:	
	UComboComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	uint8 GetComboCount() const;

	UFUNCTION(BlueprintCallable)
	void CountingCombo();

	UFUNCTION(BlueprintCallable)
	void CheckCombo();

	UFUNCTION(BlueprintCallable)
	void ResetCombo();
};