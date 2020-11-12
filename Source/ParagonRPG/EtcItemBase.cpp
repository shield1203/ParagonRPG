// Fill out your copyright notice in the Description page of Project Settings.


#include "EtcItemBase.h"
#include "Engine/Texture2D.h"
#include "UObject/ConstructorHelpers.h"
#include "Templates/SharedPointer.h"
#include "ParagonRPGGameInstance.h"

UEtcItemBase::UEtcItemBase()
{
	m_type = EItemType::ItemType_Etc;
	m_amount = 1;
}

void UEtcItemBase::Initialize(EEtcItemKind kind)
{
	m_kind = kind;
	LoadItemData();
}

void UEtcItemBase::LoadItemData()
{
	UWorld* pWorld = GetWorld();
	UParagonRPGGameInstance* pGameInstance = pWorld ? pWorld->GetGameInstance<UParagonRPGGameInstance>() : nullptr;

	if (!pGameInstance)
	{
		return;
	}

	FEtcItemData* pItemData = pGameInstance->GetDataTable(EGameDataTable::EtcItems)->FindRow<FEtcItemData>(FName(*(FString::FormatAsNumber(static_cast<uint8>(m_kind)))), FString(""));

	m_itemName = pItemData->ItemName;
	Thumbnail = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *(pItemData->Thumbnail)));
	m_itemDescription = pItemData->Description;
	m_sellingPrice = pItemData->SellPrice;
}

EEtcItemKind UEtcItemBase::GetKind() const
{
	return m_kind;
}

void UEtcItemBase::SetItemAmount(int32 amount)
{
	m_amount = amount;
}

int32 UEtcItemBase::GetItemAmount() const
{
	return m_amount;
}

bool UEtcItemBase::AddItemAmount(int32 value)
{
	m_amount += value;

	return (m_amount > 0) ? true : false;
}