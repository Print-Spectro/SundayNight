// Fill out your copyright notice in the Description page of Project Settings.


#include "MyLightFinder.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UMyLightFinder::UMyLightFinder()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMyLightFinder::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> OutLightActors;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), AMyCeilingLight::StaticClass(), TargetActorTag, OutLightActors);
	for (AActor* i : OutLightActors) {
		FoundLights.Add(Cast<AMyCeilingLight>(i));
	}
	if (OutLightActors.Num() == 0) {
		UE_LOG(LogTemp, Warning, TEXT("No Lights Actors Found"));
	}
	
}


// Called every frame
void UMyLightFinder::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

TArray<AMyCeilingLight*> UMyLightFinder::findLights() {

	return FoundLights;
}
