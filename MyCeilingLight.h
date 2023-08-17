// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyCeilingLight.generated.h"

UCLASS()
class SUNDAYNIGHT_API AMyCeilingLight : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyCeilingLight();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	class UPointLightComponent* Light;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	void toggleLight();

	bool LightState = 1;
};
