// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemShop.generated.h"

UCLASS(BlueprintType, Blueprintable)
class PARAGONRPG_API UItemShop : public UObject
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, Category = "Shop_Items")
	TArray<class UEquipmentItemBase*> EquipmentItems;

	UPROPERTY(EditDefaultsOnly, Category = "Shop_Items")
	TArray<class UConsumeItemBase*> ConsumeItems;

	UPROPERTY(EditDefaultsOnly, Category = "Shop_Items")
	TArray<class UEtcItemBase*> EtcItems;

	UFUNCTION()
	void LoadItemData();

public:
	UItemShop();

	UFUNCTION(BlueprintCallable)
	TArray<class UEquipmentItemBase*> GetEquipmentItems() const;

	UFUNCTION(BlueprintCallable)
	TArray<class UConsumeItemBase*> GetConsumeItems() const;

	UFUNCTION(BlueprintCallable)
	TArray<class UEtcItemBase*> GetEtcItems() const;

	// 유저가 아이템 구매
	UFUNCTION(BlueprintCallable)
	bool PurchaseItem(class UItemBase* item);

	// 유저가 아이템 판매
	UFUNCTION(BlueprintCallable)
	bool SellingItem(class UItemBase* item);
};
