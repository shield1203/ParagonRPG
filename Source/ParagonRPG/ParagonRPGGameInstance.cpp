#include "ParagonRPGGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "InventoryComponent.h"

UParagonRPGGameInstance::UParagonRPGGameInstance()
{
	m_curGameStep = EGameStep::GameStep_Title;

	// DataTable Load
	TArray<FString> DataTablePath;
	DataTablePath.Add(TEXT("/Game/DataTables/CharacterData"));
	DataTablePath.Add(TEXT("/Game/DataTables/EquipmentItems"));
	DataTablePath.Add(TEXT("/Game/DataTables/ConsumeItems"));
	DataTablePath.Add(TEXT("/Game/DataTables/EtcItems"));
	DataTablePath.Add(TEXT("/Game/DataTables/SkillData"));

	for (FString path : DataTablePath)
	{
		UDataTable* DataTable = LoadObject<UDataTable>(this, *path);
		
		if (DataTable)
		{
			GameDataTables.Add(DataTable);
		}
	}

	// Inventory
	m_Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
}

void UParagonRPGGameInstance::ChangeGameStep(EGameStep gameStep)
{	
	if (m_curGameStep != gameStep)
	{
		switch (gameStep)
		{
		case EGameStep::GameStep_Title: 
		{
			UGameplayStatics::OpenLevel(this, FName(TEXT("TitleMap")));			
		}
		break;
		case EGameStep::GameStep_Village:
		{
			UGameplayStatics::OpenLevel(this, FName(TEXT("VillageMap")));			
		}
		break;
		case EGameStep::GameStep_Dungeon:
		{
			UGameplayStatics::OpenLevel(this, FName(TEXT("Dungeon01")));
		}
		break;
		}
	}
}

void UParagonRPGGameInstance::SetCurGameStep(EGameStep gameStep)
{
	m_curGameStep = gameStep;
}

EGameStep UParagonRPGGameInstance::GetCurGameStep() const
{
	return m_curGameStep;
}

UDataTable* UParagonRPGGameInstance::GetDataTable(EGameDataTable table) const
{
	return GameDataTables[static_cast<uint8>(table)];
}

UInventoryComponent* UParagonRPGGameInstance::GetInventory() const
{
	return m_Inventory;
}