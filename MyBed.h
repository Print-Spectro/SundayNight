// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyBed.generated.h"

class UUserWidget;

UCLASS()
class SUNDAYNIGHT_API AMyBed : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyBed();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly)
	class USceneComponent* SleepPosition;

	UPROPERTY(EditDefaultsOnly)
	class UCameraComponent* Camera;

	UFUNCTION(BlueprintCallable)
	void sleep();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> LightOnPrompt;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> TooNoisyPrompt;

	UFUNCTION(BlueprintCallable)
	void increaseSleep();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	class AMyCharacter* Player;

	class UMyLightFinder* LightFinder;
};
