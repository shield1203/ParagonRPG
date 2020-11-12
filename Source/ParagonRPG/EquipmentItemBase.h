// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "Engine/DataTable.h"
#include "EquipmentItemBase.generated.h"

UENUM(BlueprintType, Blueprintable)
enum class EEquipmentItemKind : uint8
{
	Necklace UMETA(DisplayName = "Necklace"),
	BlueSword UMETA(DisplayName = "BlueSword"),
	Gloves00 UMETA(DisplayName = "Gloves00"),
	Gloves01 UMETA(DisplayName = "Gloves01"),
	Gloves02 UMETA(DisplayName = "Gloves02"),
	Gloves03 UMETA(DisplayName = "Gloves03"),
};

UENUM(BlueprintType, Blueprintable)
enum class EEquipmentType : uint8
{
	Sword UMETA(DisplayName = "Sword"),
	Glove UMETA(DisplayName = "Glove"),
	Accessory UMETA(DisplayName = "Accessory"),
	Dress UMETA(DisplayName = "Dress"),
	Shoes UMETA(DisplayName = "Shoes"),
};

USTRUCT(BlueprintType)
struct FEquipmentItemData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEquipmentType EquipmentType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Thumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 PurchasePrice;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SellPrice;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Power;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MP;
};

UCLASS(BlueprintType)
class PARAGONRPG_API UEquipmentItemBase : public UItemBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item_Equipment")
	EEquipmentItemKind m_kind;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item_Equipment")
	EEquipmentType m_equipmentType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item_Equipment")
	int32 m_power;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item_Equipment")
	int32 m_HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item_Equipment")
	int32 m_MP;

public:
	UEquipmentItemBase();

	UFUNCTION()
	void Initialize(EEquipmentItemKind kind);

	UFUNCTION(BlueprintCallable)
	EEquipmentItemKind GetKind() const;

	UFUNCTION(BlueprintCallable)
	EEquipmentType GetEquipmentType() const;

	UFUNCTION(BlueprintCallable)
	int32 GetItemPower() const;

	UFUNCTION(BlueprintCallable)
	int32 GetItemHP() const;

	UFUNCTION(BlueprintCallable)
	int32 GetItemMP() const;

	virtual void LoadItemData() override;

	virtual void Use(class AParagonRPGCharacter* Character) override;
};