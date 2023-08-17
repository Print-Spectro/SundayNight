// Fill out your copyright notice in the Description page of Project Settings.


#include "MyNoiseMaker.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "MyPhysicsProp.h"

// Sets default values
AMyNoiseMaker::AMyNoiseMaker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = CollisionComponent;
	
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->SetupAttachment(CollisionComponent);


// 	static ConstructorHelpers::FObjectFinder<USoundCue> HitSoundCueObject(TEXT("/ Script / Engine.SoundCue'/Game/Sounds/HitSounds/HitSound.HitSound'"));
// 	if (HitSoundCueObject.Succeeded()) {
// 		HitSoundCue = HitSoundCueObject.Object;
// 	}
}

// Called when the game starts or when spawned
void AMyNoiseMaker::BeginPlay()
{
	Super::BeginPlay();
	stopNoise();

}

// Called every frame
void AMyNoiseMaker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float DamageDealt = detectThrownActor();
	if (Active) {
		Health -= DamageDealt;
		if (Health <= 0) {
			stopNoise();
			Active = false;
		}
	}


}

void AMyNoiseMaker::playNoise() {
	float RandomOffset = FMath::FRandRange(0, AudioComponent->GetSound()->GetDuration());
	AudioComponent->Play(RandomOffset);
}

void AMyNoiseMaker::stopNoise() {
	AudioComponent->Stop();
}

float AMyNoiseMaker::detectThrownActor(){
		//temporary storage for actors
		TArray<AActor*> Actors;
		CollisionComponent->GetOverlappingActors(Actors);

		for (AActor* Actor : Actors) {
			if (Actor && Actor->ActorHasTag(TargetActorTag)) {
				
				AMyPhysicsProp* DetectedActor = Cast<AMyPhysicsProp>(Actor);
				if (DetectedActor) {
					Actor->Tags.Remove(TargetActorTag);
					DetectedActor->PlayHitSound();
					return DetectedActor->Damage;
				}

			}
		}
		return 0;
}

void AMyNoiseMaker::activate() {
	Active = true;
	Health = DefaultHealth;
	playNoise();
}