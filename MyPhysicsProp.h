// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyPhysicsProp.generated.h"

UCLASS()
class SUNDAYNIGHT_API AMyPhysicsProp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyPhysicsProp();

	UPROPERTY(EditAnywhere);
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere);
	int Damage = 4;

	UPROPERTY(EditAnywhere)
	class UAudioComponent* HitAudioComponent;

	UPROPERTY(EditAnywhere)
	class USoundBase* CollisionSound;

	void PlayHitSound();

	void setPlayerCollision(bool Collision) const;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
