// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyCeilingLight.h"
#include "MyLightSwitch.generated.h"

UCLASS()
class SUNDAYNIGHT_API AMyLightSwitch : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyLightSwitch();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	FName TargetActorTag = TEXT("Bedroom");
	
	TArray<AMyCeilingLight*> FoundLights;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly)
	class UAudioComponent* AudioComponent;

	UFUNCTION(BlueprintCallable)
	void toggleSwitch();

	class UMyOutliner* OutlineComponent;
};

