// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPhysicsProp.h"

// Sets default values
AMyPhysicsProp::AMyPhysicsProp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

}

// Called when the game starts or when spawned
void AMyPhysicsProp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPhysicsProp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



