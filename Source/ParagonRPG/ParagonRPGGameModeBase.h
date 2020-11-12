#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ParagonRPGGameModeBase.generated.h"

UCLASS(BlueprintType)
class PARAGONRPG_API AParagonRPGGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Game_UMG")
	TArray<class UUserWidget*> m_Widgets;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Game_Sound")
	UAudioComponent* m_audioComponent;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Game_Sound")
	class USoundCue* m_BGM;

	virtual void StartPlay() override;

public:
	AParagonRPGGameModeBase();

	UFUNCTION(BlueprintCallable, Category = "GameMode_UMG")
	void AddWidget(TSubclassOf<UUserWidget> NewWidgetClass);

	UFUNCTION(BlueprintCallable, Category = "GameMode_UMG")
	class UUserWidget* GetLastWidget() const;

	UFUNCTION(BlueprintCallable, Category = "GameMode_UMG")
	void RemoveLastWidget();

	UFUNCTION(BlueprintCallable, Category = "GameMode_UMG")
	int32 GetWidgetsNum() const;

	UFUNCTION(BlueprintCallable, Category = "Game_Sound")
	void PlayBGM();

	UFUNCTION(BlueprintCallable, Category = "Game_Sound")
	void StopBGM();
};
