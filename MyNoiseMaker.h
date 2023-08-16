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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UAudioComponent* AudioComponent;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* CollisionComponent;

	UFUNCTION(BlueprintCallable)
	void playNoise();

	UFUNCTION(BlueprintCallable)
	void stopNoise();

	UPROPERTY(EditDefaultsOnly, Category = "Default Parameters")
	FName TargetActorTag = FName("Thrown");

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	void detectThrownActor() const;

	UPROPERTY(EditDefaultsOnly, Category = "Default Parameters")
	int Health = 10;

private:
	bool Active;


};
