// Fill out your copyright notice in the Description page of Project Settings.


#include "GameoverTrigger.h"
#include "PuzzlePlatformsGameInstance.h"
#include "Components/BoxComponent.h"

// Sets default values
AGameoverTrigger::AGameoverTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolume"));
	RootComponent = TriggerVolume;

	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &AGameoverTrigger::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AGameoverTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameoverTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGameoverTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UPuzzlePlatformsGameInstance* GameInstance = Cast< UPuzzlePlatformsGameInstance>(GetGameInstance());
	GameInstance->LoadGameoverMenu();
}
