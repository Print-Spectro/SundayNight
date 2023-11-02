// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyCeilingLight.h"
#include "MyLightFinder.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUNDAYNIGHT_API UMyLightFinder : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMyLightFinder();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	TArray<AMyCeilingLight*> findLights();

	FName TargetActorTag = TEXT("Bedroom");

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	TArray<AMyCeilingLight*> FoundLights;
};
