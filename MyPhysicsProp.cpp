// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPhysicsProp.h"
#include "Components/AudioComponent.h"

// Sets default values
AMyPhysicsProp::AMyPhysicsProp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;


	HitAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("HitAudioComponent"));
	HitAudioComponent->SetupAttachment(Mesh);
}

// Called when the game starts or when spawned
void AMyPhysicsProp::BeginPlay()
{
	Super::BeginPlay();
	HitAudioComponent->Stop();
}

// Called every frame
void AMyPhysicsProp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//NotifyHit(Mesh, AActor*,  );
}

void AMyPhysicsProp::PlayHitSound() {
	HitAudioComponent->Play();
}

void AMyPhysicsProp::setPlayerCollision(bool Collision) const{
	ECollisionResponse ResponseType;
	if (Collision) {
		ResponseType = ECollisionResponse::ECR_Block;
		Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ResponseType);
	}
	else if (!Collision) {
		ResponseType = ECollisionResponse::ECR_Ignore;
		Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ResponseType);
	}
	else {
		UE_LOG(LogTemp, Display, TEXT("setPlayerCollisionRequiresBool"));
	}

	
}

