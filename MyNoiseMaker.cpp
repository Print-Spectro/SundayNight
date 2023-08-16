// Fill out your copyright notice in the Description page of Project Settings.


#include "MyNoiseMaker.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AMyNoiseMaker::AMyNoiseMaker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = CollisionComponent;
	
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->SetupAttachment(CollisionComponent);


}

// Called when the game starts or when spawned
void AMyNoiseMaker::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMyNoiseMaker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Active) {

	}


}

void AMyNoiseMaker::playNoise() {
	float RandomOffset = FMath::FRandRange(0, AudioComponent->GetSound()->GetDuration());
	AudioComponent->Play(RandomOffset);
}

void AMyNoiseMaker::stopNoise() {
	AudioComponent->Stop();
}

void AMyNoiseMaker::detectThrownActor() const{
	
		TArray<AActor*> Actors;
		CollisionComponent->GetOverlappingActors(Actors);

		for (AActor* Actor : Actors) {
			if (Actor->ActorHasTag(TargetActorTag)) {
				Actor->Tags.Remove(TargetActorTag);
				Health -= Actor->Damage;
			}
		}
		

}