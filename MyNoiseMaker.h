// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyNoiseMaker.generated.h"

UCLASS()
class SUNDAYNIGHT_API AMyNoiseMaker : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyNoiseMaker();

	UPROPERTY(EditAnywhere)
	class UAudioComponent* AudioComponent;


	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* CollisionComponent;

	UFUNCTION(BlueprintCallable)
	void playNoise();

	UFUNCTION(BlueprintCallable)
	void stopNoise();

	UFUNCTION(BlueprintCallable)
	void activate();

	UPROPERTY(EditDefaultsOnly, Category = "Default Parameters")
	FName TargetActorTag = FName("Thrown");

	UPROPERTY(EditAnywhere, Category = "Default Parameters")
	int DefaultHealth = 10;

	bool Active = false;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float getBassIntensity();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	float detectThrownActor();

	

	int Health;

	


};
