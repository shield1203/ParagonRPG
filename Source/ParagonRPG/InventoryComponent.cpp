// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "ItemBase.h"
#include "EquipmentItemBase.h"
#include "ConsumeItemBase.h"
#include "EtcItemBase.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	money = 100000;

	UE_LOG(LogTemp, Warning, TEXT("Create Inventory"));
}

// Called when the game starts
//void UInventoryComponent::BeginPlay()
//{
//	Super::BeginPlay();
//
//	// ...
//	
//}


// Called every frame
//void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	// ...
//}

int32 UInventoryComponent::GetCurMoney() const
{
	return money;
}

TArray<UEquipmentItemBase*> UInventoryComponent::GetEquipmentItems() const
{
	return EquipmentItems;
}

TMap<EConsumeItemKind, UConsumeItemBase*> UInventoryComponent::GetConsumeItems() const
{
	return CunsumeItems;
}

TMap<EEtcItemKind, UEtcItemBase*> UInventoryComponent::GetEtcItems() const
{
	return EtcItems;
}

bool UInventoryComponent::ChargeMoney(int32 cost)
{
	if (money + cost >= 0)
	{
		money += cost;
		return true;
	}

	return false;
}

bool UInventoryComponent::AddItem(UItemBase* item)
{
	if (nullptr == item) return false;

	bool bResult;

	switch (item->GetItemType())
	{
	case EItemType::ItemType_Equipment:
		bResult = AddEquipmentItem(item);
	break;
	case EItemType::ItemType_Consume:
		bResult = AddConsumeItem(item);
	break;
	case EItemType::ItemType_Etc:
		bResult = AddEtcItem(item);
	break;
	}

	return bResult;
}

bool UInventoryComponent::AddEquipmentItem(UItemBase* item)
{
	UEquipmentItemBase* pEquipmentItem = Cast<UEquipmentItemBase>(item);

	if (nullptr == pEquipmentItem) return false;
	
	EquipmentItems.Add(pEquipmentItem);

	return true;
}

bool UInventoryComponent::AddConsumeItem(UItemBase* item)
{
	UConsumeItemBase* pConsumeItem = Cast<UConsumeItemBase>(item);

	if (nullptr == pConsumeItem) return false;

	if (CunsumeItems.Contains(pConsumeItem->GetKind()))
	{
		CunsumeItems[pConsumeItem->GetKind()]->AddItemAmount(pConsumeItem->GetItemAmount());
	}
	else
	{
		CunsumeItems.Add(pConsumeItem->GetKind(), pConsumeItem);
	}

	return true;
}

bool UInventoryComponent::AddEtcItem(UItemBase* item)
{
	UEtcItemBase* pEtcItem = Cast<UEtcItemBase>(item);

	if (nullptr == pEtcItem) return false;

	if (EtcItems.Contains(pEtcItem->GetKind()))
	{
		EtcItems[pEtcItem->GetKind()]->AddItemAmount(pEtcItem->GetItemAmount());
	}
	else
	{
		EtcItems.Add(pEtcItem->GetKind(), pEtcItem);
	}

	return true;
}

bool UInventoryComponent::RemoveItem(UItemBase* item)
{
	if (nullptr == item) return false;

	bool bResult;

	switch (item->GetItemType())
	{
	case EItemType::ItemType_Equipment:
		bResult = RemoveEquipmentItem(item);
	break;
	case EItemType::ItemType_Consume:
		bResult = RemoveConsumeItem(item);
	break;
	case EItemType::ItemType_Etc:
		bResult = RemoveEtcItem(item);
	break;
	}

	return bResult;
}

bool UInventoryComponent::RemoveEquipmentItem(UItemBase* item)
{
	UEquipmentItemBase* pEquipmentItem = Cast<UEquipmentItemBase>(item);

	if (nullptr == pEquipmentItem) return false;

	EquipmentItems.Remove(pEquipmentItem);

	return true;
}

bool UInventoryComponent::RemoveConsumeItem(UItemBase* item)
{
	UConsumeItemBase* pConsumeItem = Cast<UConsumeItemBase>(item);

	if (nullptr == pConsumeItem) return false;

	if (CunsumeItems.Contains(pConsumeItem->GetKind()))
	{
		if (!CunsumeItems[pConsumeItem->GetKind()]->AddItemAmount(-1))
		{
			CunsumeItems.Remove(pConsumeItem->GetKind());
		}
	}
	else
	{
		return false;
	}

	return true;
}

bool UInventoryComponent::RemoveEtcItem(UItemBase* item)
{
	UEtcItemBase* pEtcItem = Cast<UEtcItemBase>(item);

	if (nullptr == pEtcItem) return false;

	if (EtcItems.Contains(pEtcItem->GetKind()))
	{
		if (!EtcItems[pEtcItem->GetKind()]->AddItemAmount(-1))
		{
			EtcItems.Remove(pEtcItem->GetKind());
		}
	}
	else
	{
		return false;
	}

	return true;
}