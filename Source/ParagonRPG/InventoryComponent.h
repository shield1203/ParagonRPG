// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemBase.h"
#include "EquipmentItemBase.h"
#include "ConsumeItemBase.h"
#include "EtcItemBase.h"
#include "InventoryComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PARAGONRPG_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = "Usable_Money")
	int32 money;

	//UPROPERTY(EditDefaultsOnly, Category = "Inventory_Items")
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory_Items")
	TArray<UEquipmentItemBase*> EquipmentItems;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory_Items")
	TMap<EConsumeItemKind, UConsumeItemBase*> CunsumeItems;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory_Items")
	TMap<EEtcItemKind, UEtcItemBase*> EtcItems;

public:	
	// Sets default values for this component's properties
	UInventoryComponent();


protected:
	// Called when the game starts
	//virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	int32 GetCurMoney() const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	TArray<UEquipmentItemBase*> GetEquipmentItems() const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	TMap<EConsumeItemKind, UConsumeItemBase*> GetConsumeItems() const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	TMap<EEtcItemKind, UEtcItemBase*> GetEtcItems() const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool ChargeMoney(int32 cost);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddItem(UItemBase* item);

	bool AddEquipmentItem(UItemBase* item);

	bool AddConsumeItem(UItemBase* item);

	bool AddEtcItem(UItemBase* item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool RemoveItem(UItemBase* item);

	bool RemoveEquipmentItem(UItemBase* item);

	bool RemoveConsumeItem(UItemBase* item);

	bool RemoveEtcItem(UItemBase* item);
};
