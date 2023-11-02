//Finds all lights with a specific tag


#include "MyLightFinder.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UMyLightFinder::UMyLightFinder()
{
	PrimaryComponentTick.bCanEverTick = false;
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
}

TArray<AMyCeilingLight*> UMyLightFinder::findLights() {

	return FoundLights;
}
