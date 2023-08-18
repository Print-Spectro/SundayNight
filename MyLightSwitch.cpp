// Fill out your copyright notice in the Description page of Project Settings.


#include "MyLightSwitch.h"
#include "Kismet/GameplayStatics.h"
#include "MyOutliner.h"
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

	OutlineComponent = CreateDefaultSubobject<UMyOutliner>(TEXT("OutlineComponent"));
}

// Called when the game starts or when spawned
void AMyLightSwitch::BeginPlay()
{
	Super::BeginPlay();

	//Creating an array of MyCeilingLight pointers to allow toggling 
	TArray<AActor*> OutLightActors;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), AMyCeilingLight::StaticClass(), TargetActorTag, OutLightActors);
	for (AActor* i : OutLightActors) {
		FoundLights.Add(Cast<AMyCeilingLight>(i));
	}
	if (OutLightActors.Num() == 0){
		//Warning helps debug if your tags don't match. 
		UE_LOG(LogTemp, Warning, TEXT("No Lights Actors Found"));
	}
	AudioComponent->Stop();

	OutlineComponent->setOutline(0);
}

// Called every frame
void AMyLightSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



void AMyLightSwitch::toggleSwitch() {
	//Plays switch sound, rotates 180 degrees to give the impression of flipping the switch
	//triggers the toggeLight function of all lights found with the corresponding tag
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