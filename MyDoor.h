// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyDoor.generated.h"

UCLASS()
class SUNDAYNIGHT_API AMyDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyDoor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UFUNCTION(BlueprintCallable)
	int getOpenDirection();

	UFUNCTION(BlueprintCallable)
	void toggleOpen(int Direction);

	UPROPERTY(EditAnywhere, Category = "Door Defaults")
	bool OpenState = 0;

	UPROPERTY(EditAnywhere)
	class USoundBase* OpenSound;

	FRotator InitialRotation;
};
