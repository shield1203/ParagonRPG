#pragma once

#include "CoreMinimal.h"
#include "ParagonRPGGameModeBase.h"
#include "DungeonGameMode.generated.h"

UCLASS()
class PARAGONRPG_API ADungeonGameMode : public AParagonRPGGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Game_UMG", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> m_gameClearWidget;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Game_UMG", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> m_gameOverWidget;

protected:
	virtual void StartPlay() override;

public:
	ADungeonGameMode();

	UFUNCTION(BlueprintCallable, Category = "GameMode_UMG")
	void GameClear();

	UFUNCTION(BlueprintCallable, Category = "GameMode_UMG")
	void GameOver();
};
