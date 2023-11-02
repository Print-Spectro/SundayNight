// Fill out your copyright notice in the Description page of Project Settings.
#include "MyBed.h"
#include "MyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "MyNoiseMaker.h"
#include "MyLightFinder.h"
#include "Components/SceneComponent.h"

//widgets
#include "Components/Widget.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"


// Sets default values
AMyBed::AMyBed()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	SleepPosition = CreateDefaultSubobject<USceneComponent>(TEXT("SleepPosition"));
	SleepPosition->SetupAttachment(Mesh);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("BedCamera"));
	Camera->SetupAttachment(Mesh);

	LightFinder = CreateDefaultSubobject<UMyLightFinder>(TEXT("LightFinder"));
}

// Called when the game starts or when spawned
void AMyBed::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyBed::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Player = Cast<AMyCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

void AMyBed::increaseSleep(){
	if (Player != nullptr){
	Player->increaseScore();
	}
}

void AMyBed::sleep() {
	if (Player != nullptr) {
		// Sleeping is only possible if the current noise maker is inactive and
		// the light is off
		if (Player->CurrentNoiseMaker != nullptr &&
			!Player->CurrentNoiseMaker->Active &&
			!LightFinder->findLights()[0]->LightState) {
			UGameplayStatics::GetPlayerController(GetWorld(), 0)->Possess(this);
			// Set player sleeping state
			Player->startIncreaseScore();
			Player->release();
			Player->stopWalkSound();
		}
		else if (Player->CurrentNoiseMaker->Active) {
			if (TooNoisyPrompt == nullptr) {
				return;
				UE_LOG(LogTemp, Warning, TEXT("AMyBed::sleep: No TooNoisyPrompt selected"));
			}
			UUserWidget* PromptInstance = CreateWidget<UUserWidget>(GetWorld(), TooNoisyPrompt);
			PromptInstance->AddToViewport();
		}
		else if (LightFinder->findLights()[0]->LightState) {
			if (LightOnPrompt == nullptr) {
				UE_LOG(LogTemp, Warning, TEXT("AMyBed::sleep: No LightOnPrompt Selected"));
				return;
			}
			UUserWidget* LightOnPromptInstance = CreateWidget<UUserWidget>(GetWorld(), LightOnPrompt);
			LightOnPromptInstance->AddToViewport();
		}
	}
}
