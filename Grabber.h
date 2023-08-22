// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUNDAYNIGHT_API UGrabber : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();
	UFUNCTION(BlueprintCallable)
	void Release();

	UFUNCTION(BlueprintCallable)
	void Grab();

	UFUNCTION(BlueprintCallable)
	void Throw();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:
	UPROPERTY(EditAnywhere)
	float MaxGrabDistance = 180;

	UPROPERTY(EditAnywhere)
	float GrabRadius = 20;

	UPROPERTY(EditAnywhere)
	float HoldDistance = 100;

	UFUNCTION(BlueprintCallable)
	UPhysicsHandleComponent* GetPhysicsHandle() const;

	UFUNCTION(BlueprintCallable)
	bool GetGrabbableInReach(FHitResult& OutHitResult) const;

	UPROPERTY(EditDefaultsOnly)
	float MaximumThrowVelocity = 5000;

	UPROPERTY(EditDefaultsOnly)
	float ThrowImpulse = 100000;

};
