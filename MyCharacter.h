// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "MyCharacter.generated.h"

UCLASS()
class SUNDAYNIGHT_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

	class AMyNoiseMaker* CurrentNoiseMaker;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void increaseScore();

	void startIncreaseScore();

	UFUNCTION(BlueprintCallable)
	void restartLevel();

	void release();

	void stopWalkSound();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnhancedInput")
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnhancedInput")
	class UMyInputConfigData* InputActions;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	class UCameraComponent* PlayerCamera;

	//Handle move input
	void Move(const FInputActionValue& Value);

	//Handle Look input 
	void Look(const FInputActionValue& Value);

	//Handle interact input
	void grab(const FInputActionValue& Value);

	void playNoise();

	UPROPERTY(BlueprintReadOnly);
	int score = 0;

	UPROPERTY(EditDefaultsOnly, meta = (ToolTip = "Grab distance in cm"), category = "Game Parameters")
	float InteractDistance = 200;

	//stores previously hovered outline compoent so that the outline can be switched off
	class UMyOutliner* PreviousHovered;

	TArray<AActor*> FoundNoiseMakers;

	void hoverOutlineInteractable();

	UFUNCTION(BlueprintCallable)
	AActor* getInteractableLookingAt();

	void interact();

	void wakeUp();

	UPROPERTY(EditDefaultsOnly)
	class UAudioComponent* AudioComponent;

	void walkSound();

	UPROPERTY(EditDefaultsOnly, meta = (ToolTip = "Delay between noise in s"), category = "Game Parameters")
	float NoiseDelay = 7;

private:
	class UCapsuleComponent* CapsuleComponent;

	class UGrabber* GrabComponent;

	UPROPERTY()
	FTimerHandle NoiseTimer;

	FTimerHandle ScoreTimer;

	FTimerHandle WakeupTimer;
};
