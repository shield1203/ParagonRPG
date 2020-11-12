// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemShop.h"
#include "ParagonRPGGameInstance.h"
#include "InventoryComponent.h"
#include "ItemBase.h"
#include "EquipmentItemBase.h"
#include "ConsumeItemBase.h"
#include "EtcItemBase.h"

UItemShop::UItemShop()
{
	LoadItemData();
}

void UItemShop::LoadItemData()
{
	// Equipment Item
	UEquipmentItemBase* EquipmentItem1 = CreateDefaultSubobject<UEquipmentItemBase>(TEXT("Item_BlueSword"));
	EquipmentItem1->Initialize(EEquipmentItemKind::BlueSword);
	EquipmentItems.Add(EquipmentItem1);

	UEquipmentItemBase* EquipmentItem2 = CreateDefaultSubobject<UEquipmentItemBase>(TEXT("Item_Necklace"));
	EquipmentItem2->Initialize(EEquipmentItemKind::Necklace);
	EquipmentItems.Add(EquipmentItem2);

	UEquipmentItemBase* EquipmentItem3 = CreateDefaultSubobject<UEquipmentItemBase>(TEXT("Item_Gloves00"));
	EquipmentItem3->Initialize(EEquipmentItemKind::Gloves00);
	EquipmentItems.Add(EquipmentItem3);

	UEquipmentItemBase* EquipmentItem4 = CreateDefaultSubobject<UEquipmentItemBase>(TEXT("Item_Gloves01"));
	EquipmentItem4->Initialize(EEquipmentItemKind::Gloves01);
	EquipmentItems.Add(EquipmentItem4);

	UEquipmentItemBase* EquipmentItem5 = CreateDefaultSubobject<UEquipmentItemBase>(TEXT("Item_Gloves02"));
	EquipmentItem5->Initialize(EEquipmentItemKind::Gloves02);
	EquipmentItems.Add(EquipmentItem5);

	UEquipmentItemBase* EquipmentItem6 = CreateDefaultSubobject<UEquipmentItemBase>(TEXT("Item_Gloves03"));
	EquipmentItem6->Initialize(EEquipmentItemKind::Gloves03);
	EquipmentItems.Add(EquipmentItem6);

	// Consume Item
	UConsumeItemBase* ConsumeItem1 = CreateDefaultSubobject<UConsumeItemBase>(TEXT("Item_RedPotion"));
	ConsumeItem1->Initialize(EConsumeItemKind::RedPotion);
	ConsumeItems.Add(ConsumeItem1);

	UConsumeItemBase* ConsumeItem2 = CreateDefaultSubobject<UConsumeItemBase>(TEXT("Item_BluePotion"));
	ConsumeItem2->Initialize(EConsumeItemKind::BluePotion);
	ConsumeItems.Add(ConsumeItem2);

	UConsumeItemBase* ConsumeItem3 = CreateDefaultSubobject<UConsumeItemBase>(TEXT("Item_WhitePotion"));
	ConsumeItem3->Initialize(EConsumeItemKind::WhitePotion);
	ConsumeItems.Add(ConsumeItem3);

	UConsumeItemBase* ConsumeItem4 = CreateDefaultSubobject<UConsumeItemBase>(TEXT("Item_Elixir"));
	ConsumeItem4->Initialize(EConsumeItemKind::Elixir);
	ConsumeItems.Add(ConsumeItem4);
}

TArray<UEquipmentItemBase*> UItemShop::GetEquipmentItems() const
{
	return EquipmentItems;
}

TArray<UConsumeItemBase*> UItemShop::GetConsumeItems() const
{
	return ConsumeItems;
}

TArray<UEtcItemBase*> UItemShop::GetEtcItems() const
{
	return EtcItems;
}

bool UItemShop::PurchaseItem(UItemBase* item)
{
	UWorld* pWorld = GetWorld();
	UParagonRPGGameInstance* pGameInstance = pWorld ? pWorld->GetGameInstance<UParagonRPGGameInstance>() : nullptr;

	if (!pGameInstance)
	{
		return false;
	}

	UInventoryComponent* pInventory = pGameInstance->GetInventory();

	if (!pInventory->ChargeMoney(-item->GetPurchasePrice()))
	{
		return false;
	}

	switch (item->GetItemType())
	{
	case EItemType::ItemType_Equipment:
	{
		UEquipmentItemBase* pAddItem = NewObject<UEquipmentItemBase>(pWorld, UEquipmentItemBase::StaticClass());
		pAddItem->Initialize((Cast<UEquipmentItemBase>(item))->GetKind());
		pInventory->AddItem(pAddItem);
	}
	break;
	case EItemType::ItemType_Consume:
	{
		UConsumeItemBase* pAddItem = NewObject<UConsumeItemBase>(pWorld, UConsumeItemBase::StaticClass());
		pAddItem->Initialize((Cast<UConsumeItemBase>(item))->GetKind());
		pInventory->AddItem(pAddItem);
	}
	break;
	case EItemType::ItemType_Etc:
	{
		UEtcItemBase* pAddItem = NewObject<UEtcItemBase>(pWorld, UEtcItemBase::StaticClass());
		pAddItem->Initialize((Cast<UEtcItemBase>(item))->GetKind());
		pInventory->AddItem(pAddItem);
	}
	break;
	}

	return true;
}

bool UItemShop::SellingItem(UItemBase* item)
{
	UWorld* pWorld = GetWorld();
	UParagonRPGGameInstance* pGameInstance = pWorld ? pWorld->GetGameInstance<UParagonRPGGameInstance>() : nullptr;

	if (!pGameInstance)
	{
		return false;
	}

	UInventoryComponent* pInventory = pGameInstance->GetInventory();

	pInventory->ChargeMoney(item->GetSellingPrice());
	pInventory->RemoveItem(item);

	return true;
}