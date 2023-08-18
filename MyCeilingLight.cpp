// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCeilingLight.h"
#include "Components/PointLightComponent.h"

// Sets default values
AMyCeilingLight::AMyCeilingLight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("Light"));
	Light->SetupAttachment(Mesh);
}

// Called when the game starts or when spawned
void AMyCeilingLight::BeginPlay()
{
	Super::BeginPlay();
	Light->SetVisibility(LightState);
}

// Called every frame
void AMyCeilingLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyCeilingLight::toggleLight() {
	LightState = !LightState;
	Light->SetVisibility(LightState);
}

