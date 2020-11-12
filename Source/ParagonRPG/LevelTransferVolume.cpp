#include "LevelTransferVolume.h"
#include "Engine/Classes/Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

ALevelTransferVolume::ALevelTransferVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TransferVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TransferVolume"));
	RootComponent = TransferVolume;
	TransferVolume->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
}

//void ALevelTransferVolume::BeginPlay()
//{
//	Super::BeginPlay();
//	
//}

void ALevelTransferVolume::NotifyActorBeginOverlap(AActor* OtherActor)
{
    APawn* Pawn = Cast<APawn>(OtherActor);

    if (Pawn != nullptr)
    {
        UGameplayStatics::OpenLevel(this, TransferLevelName);
        UE_LOG(LogTemp, Error, TEXT("Level Trans"));
    }
}

void ALevelTransferVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}