// Fill out your copyright notice in the Description page of Project Settings.


#include "ConsumeItemBase.h"
#include "Engine/Texture2D.h"
#include "UObject/ConstructorHelpers.h"
#include "Templates/SharedPointer.h"
#include "ParagonRPGGameInstance.h"

UConsumeItemBase::UConsumeItemBase()
{
	m_type = EItemType::ItemType_Consume;
	m_amount = 1;
}

void UConsumeItemBase::Initialize(EConsumeItemKind kind)
{
	m_kind = kind;
	LoadItemData();
	UE_LOG(LogTemp, Warning, TEXT("%d %s %s"), kind, *m_itemName, *m_itemDescription);
}

void UConsumeItemBase::LoadItemData()
{
	UWorld* pWorld = GetWorld();

	UParagonRPGGameInstance* pGameInstance = pWorld ? pWorld->GetGameInstance<UParagonRPGGameInstance>() : nullptr;

	if (!pGameInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed GameInstance : ConsumeItemBase"));
		return;
	}

	FConsumeItemData* pItemData = pGameInstance->GetDataTable(EGameDataTable::ConsumeItems)->FindRow<FConsumeItemData>(FName(*(FString::FormatAsNumber(static_cast<uint8>(m_kind)))), FString(""));

	m_itemName = pItemData->ItemName;
	Thumbnail = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *(pItemData->Thumbnail)));
	m_itemDescription = pItemData->Description;
	m_purchasePrice = pItemData->PurchasePrice;
	m_sellingPrice = pItemData->SellPrice;
	m_RecoveryHP = pItemData->RecoveryHP;
	m_RecoveryMP = pItemData->RecoveryMP;
}

EConsumeItemKind UConsumeItemBase::GetKind() const
{
	return m_kind;
}

void UConsumeItemBase::SetItemAmount(int32 amount)
{
	m_amount = amount;
}

int32 UConsumeItemBase::GetItemAmount() const
{
	return m_amount;
}

bool UConsumeItemBase::AddItemAmount(int32 value)
{
	m_amount += value;

	return (m_amount > 0) ? true : false;
}

void UConsumeItemBase::Use(class AParagonRPGCharacter* Character)
{

}