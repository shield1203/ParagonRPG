// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NPCCharacterBase.generated.h"

UCLASS()
class PARAGONRPG_API ANPCCharacterBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANPCCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "NPC_UMG")
	void VisibleButtonWidget(bool visibleValue);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* CollisionVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMeshComponent* NPCVisual;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Game_UMG")
	TSubclassOf<class UUserWidget> m_ButtonWidgetClass;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Game_UMG")
	class UUserWidget* m_buttonWidget;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

};
