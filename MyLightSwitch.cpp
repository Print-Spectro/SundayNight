// Fill out your copyright notice in the Description page of Project Settings.


#include "MyLightSwitch.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

// Sets default values
AMyLightSwitch::AMyLightSwitch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->SetupAttachment(Mesh);
}

// Called when the game starts or when spawned
void AMyLightSwitch::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> OutLightActors;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), AMyCeilingLight::StaticClass(), TargetActorTag, OutLightActors);
	for (AActor* i : OutLightActors) {
		FoundLights.Add(Cast<AMyCeilingLight>(i));
	}
	if (OutLightActors.Num() == 0){
		UE_LOG(LogTemp, Warning, TEXT("No Lights Actors Found"));
	}
	AudioComponent->Stop();
}

// Called every frame
void AMyLightSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



void AMyLightSwitch::toggleSwitch() {
	if (AudioComponent->Sound != nullptr) {
		AudioComponent->Play();
	}
	Mesh->AddLocalRotation(FRotator(0,0 , 180));
	if (FoundLights.Num() > 0){
		for (AMyCeilingLight* i : FoundLights) {
			i->toggleLight();
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No Lights Found"));
	}

}