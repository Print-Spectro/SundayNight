// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyGameManager.generated.h"


class AMyNoiseMaker; //forward declaration makes the array below work

UCLASS()
class SUNDAYNIGHT_API AMyGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyGameManager();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class AMyCharacter* PlayerCharacter;

	class AMyBed* Bed;

	TArray<AMyNoiseMaker*> FoindNoiseMakers;
};
