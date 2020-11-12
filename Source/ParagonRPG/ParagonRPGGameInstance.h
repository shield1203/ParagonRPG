#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ParagonRPGGameInstance.generated.h"

UENUM(BlueprintType)
enum class EGameStep : uint8
{
	GameStep_Title UMETA(DisplayName = "GameStep_Title"),
	GameStep_Village UMETA(DisplayName = "GameStep_Village"),
	GameStep_Dungeon UMETA(DisplayName = "GameStep_Dungeon")
};

UENUM(BlueprintType)
enum class EGameDataTable : uint8
{
	CharacterData UMETA(DisplayName = "DataTable_Character"),
	EquipmentItems UMETA(DisplayName = "DataTable_Equipment"),
	ConsumeItems UMETA(DisplayName = "DataTable_Consume"),
	EtcItems UMETA(DisplayName = "DataTable_Etc"),
	SkillData UMETA(DisplayName = "DataTable_Skill"),
};

UCLASS()
class PARAGONRPG_API UParagonRPGGameInstance : public UGameInstance
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, Category = "GameStep")
	EGameStep m_curGameStep;

	UPROPERTY(EditAnywhere, Category = "GameDataTables")
	TArray<class UDataTable*> GameDataTables;

	UPROPERTY(EditAnywhere, Category = "Game_Inventory")
	class UInventoryComponent* m_Inventory;
public:
	UParagonRPGGameInstance();

	UFUNCTION(BlueprintCallable)
	void ChangeGameStep(EGameStep gameStep);

	UFUNCTION(BlueprintCallable)
	void SetCurGameStep(EGameStep gameStep);

	UFUNCTION(BlueprintCallable)
	EGameStep GetCurGameStep() const;

	UFUNCTION(BlueprintCallable)
	class UDataTable* GetDataTable(EGameDataTable table) const;

	UFUNCTION(BlueprintCallable)
	class UInventoryComponent* GetInventory() const;
};