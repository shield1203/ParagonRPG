// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "Engine/DataTable.h"
#include "ConsumeItemBase.generated.h"

UENUM(BlueprintType)
enum class EConsumeItemKind : uint8
{
	RedPotion UMETA(DisplayName = "RedPotion"),
	BluePotion UMETA(DisplayName = "BluePotion"),
	WhitePotion UMETA(DisplayName = "WhitePotion"),
	Elixir UMETA(DisplayName = "Elixir"),
};

USTRUCT(BlueprintType)
struct FConsumeItemData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Thumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 PurchasePrice;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SellPrice;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 RecoveryHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 RecoveryMP;
};

UCLASS(BlueprintType)
class PARAGONRPG_API UConsumeItemBase : public UItemBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item_Consume")
	EConsumeItemKind m_kind;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item_Consume")
	int32 m_amount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item_Consume")
	int32 m_RecoveryHP;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item_Consume")
	int32 m_RecoveryMP;

public:
	UConsumeItemBase();

	UFUNCTION()
	void Initialize(EConsumeItemKind kind);

	virtual void LoadItemData() override;

	virtual void Use(class AParagonRPGCharacter* Character) override;

	UFUNCTION(BlueprintCallable)
	EConsumeItemKind GetKind() const;

	UFUNCTION(BlueprintCallable)
	void SetItemAmount(int32 amount);

	UFUNCTION(BlueprintCallable)
	int32 GetItemAmount() const;

	// If amount is minus return false
	UFUNCTION(BlueprintCallable)
	bool AddItemAmount(int32 value);
};
