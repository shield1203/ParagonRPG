#include "ItemBase.h"
#include "Engine/Texture2D.h"

EItemType UItemBase::GetItemType() const
{
	return m_type;
}

UTexture2D* UItemBase::GetThumbnail() const
{
	return Thumbnail;
}

FString UItemBase::GetItemName() const
{
	return m_itemName;
}

FString UItemBase::GetItemDescription() const
{
	return m_itemDescription;
}

int32 UItemBase::GetPurchasePrice() const
{
	return m_purchasePrice;
}

int32 UItemBase::GetSellingPrice() const
{
	return m_sellingPrice;
}