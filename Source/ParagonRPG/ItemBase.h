// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemBase.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	ItemType_Equipment UMETA(DisplayName = "Equipment"),
	ItemType_Consume UMETA(DisplayName = "Consume"),
	ItemType_Etc UMETA(DisplayName = "Etc")
};

UCLASS(BlueprintType, Blueprintable)
class PARAGONRPG_API UItemBase : public UObject
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Item")
	EItemType m_type;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	//class UStaticMesh* PickupMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Item")
	class UTexture2D* Thumbnail;

	UPROPERTY(EditDefaultsOnly, Category = "Item")
	FString m_itemName;

	UPROPERTY(EditDefaultsOnly, Category = "Item", meta = (MultiLine = true))
	FString m_itemDescription;

	UPROPERTY(EditDefaultsOnly, Category = "Item")
	int32 m_purchasePrice;

	UPROPERTY(EditDefaultsOnly, Category = "Item")
	int32 m_sellingPrice;

public:
	UItemBase() {};

	UFUNCTION(BlueprintCallable)
	EItemType GetItemType() const;

	UFUNCTION(BlueprintCallable)
	class UTexture2D* GetThumbnail() const;

	UFUNCTION(BlueprintCallable)
	FString GetItemName() const;

	UFUNCTION(BlueprintCallable)
	FString GetItemDescription() const;

	UFUNCTION(BlueprintCallable)
	int32 GetPurchasePrice() const;

	UFUNCTION(BlueprintCallable)
	int32 GetSellingPrice() const;

	virtual void LoadItemData() {};

	virtual void Use(class AParagonRPGCharacter* Character) {};
};
