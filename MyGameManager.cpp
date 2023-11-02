// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameManager.h"
#include "MyCharacter.h"
#include "MyBed.h"
#include "MyNoiseMaker.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyGameManager::AMyGameManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMyGameManager::BeginPlay()
{
	Super::BeginPlay();
	//Getting all the actors that need to be communicated with
	PlayerCharacter = Cast<AMyCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), AMyCharacter::StaticClass()));
	Bed = Cast<AMyBed>(UGameplayStatics::GetActorOfClass(GetWorld(), AMyBed::StaticClass()));
	TArray<AActor*> FoundNoiseActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyNoiseMaker::StaticClass(), FoundNoiseActors);
	for (AActor*  NoiseActor: FoundNoiseActors) {
		FoindNoiseMakers.Add(Cast<AMyNoiseMaker>(NoiseActor));
	}
}

// Called every frame
void AMyGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

