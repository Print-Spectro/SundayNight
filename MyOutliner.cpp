// Fill out your copyright notice in the Description page of Project Settings.


#include "MyOutliner.h"

// Sets default values for this component's properties
UMyOutliner::UMyOutliner()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UMyOutliner::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UMyOutliner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UMyOutliner::setOutline(bool state = 0) {
	UStaticMeshComponent* Result = GetOwner()->FindComponentByClass<UStaticMeshComponent>();
	Result->SetRenderCustomDepth(state);
}