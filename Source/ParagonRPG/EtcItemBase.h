// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "Engine/DataTable.h"
#include "EtcItemBase.generated.h"

UENUM(BlueprintType)
enum class EEtcItemKind : uint8
{
	RedFlower UMETA(DisplayName = "RedFlower"),
	StudyBook UMETA(DisplayName = "StudyBook"),
};

USTRUCT(BlueprintType)
struct FEtcItemData : public FTableRowBase
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
	int32 SellPrice;
};

UCLASS(BlueprintType)
class PARAGONRPG_API UEtcItemBase : public UItemBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item_Etc")
	EEtcItemKind m_kind;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item_Etc")
	int32 m_amount;

public:
	UEtcItemBase();

	UFUNCTION()
	void Initialize(EEtcItemKind kind);

	virtual void LoadItemData() override;

	UFUNCTION(BlueprintCallable)
	EEtcItemKind GetKind() const;

	UFUNCTION(BlueprintCallable)
	void SetItemAmount(int32 amount);

	UFUNCTION(BlueprintCallable)
	int32 GetItemAmount() const;

	// If amount is minus return false
	UFUNCTION(BlueprintCallable)
	bool AddItemAmount(int32 value);
};
