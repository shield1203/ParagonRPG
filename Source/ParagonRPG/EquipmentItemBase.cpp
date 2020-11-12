// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentItemBase.h"
#include "Engine/Texture2D.h"
#include "UObject/ConstructorHelpers.h"
#include "Templates/SharedPointer.h"
#include "ParagonRPGGameInstance.h"

UEquipmentItemBase::UEquipmentItemBase()
{
	m_type = EItemType::ItemType_Equipment;
}

void UEquipmentItemBase::Initialize(EEquipmentItemKind kind)
{
	m_kind = kind;
	LoadItemData();
}

EEquipmentItemKind UEquipmentItemBase::GetKind() const
{
	return m_kind;
}

EEquipmentType UEquipmentItemBase::GetEquipmentType() const
{
	return m_equipmentType;
}

int32 UEquipmentItemBase::GetItemPower() const
{
	return m_power;
}

int32 UEquipmentItemBase::GetItemHP() const
{
	return m_HP;
}

int32 UEquipmentItemBase::GetItemMP() const
{
	return m_MP;
}

void UEquipmentItemBase::LoadItemData()
{
	UWorld* pWorld = GetWorld();
	UParagonRPGGameInstance* pGameInstance = pWorld ? pWorld->GetGameInstance<UParagonRPGGameInstance>() : nullptr;

	if (!pGameInstance)
	{
		return;
	}

	FEquipmentItemData* pItemData = pGameInstance->GetDataTable(EGameDataTable::EquipmentItems)->FindRow<FEquipmentItemData>(FName(*(FString::FormatAsNumber(static_cast<uint8>(m_kind)))), FString(""));

	m_itemName = pItemData->ItemName;
	m_equipmentType = pItemData->EquipmentType;
	Thumbnail = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *(pItemData->Thumbnail)));
	m_itemDescription = pItemData->Description;
	m_purchasePrice = pItemData->PurchasePrice;
	m_sellingPrice = pItemData->SellPrice;
	m_power = pItemData->Power;
	m_HP = pItemData->HP;
	m_MP = pItemData->MP;
}

void UEquipmentItemBase::Use(class AParagonRPGCharacter* Character)
{

}