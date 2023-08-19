// Fill out your copyright notice in the Description page of Project Settings.


#include "MyDoor.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Sound/SoundBase.h"
#include "MyCharacter.h"

// Sets default values
AMyDoor::AMyDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
}


// Called when the game starts or when spawned
void AMyDoor::BeginPlay()
{
	Super::BeginPlay();
	InitialRotation = GetActorRotation();
	SetActorRotation(InitialRotation + FRotator(0, 90, 0) * OpenState);

}

// Called every frame
void AMyDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

int AMyDoor::getOpenDirection() {
	//Used to determine which side of the door the player is on so that the door always opens away. 
	FQuat MeshAngle = Mesh->GetComponentQuat();
	AActor* Player = Cast<AMyCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	FVector RelativeLookingAt = UKismetMathLibrary::Quat_RotateVector(MeshAngle.Inverse(), Player->GetActorLocation() - Mesh->GetComponentLocation());

	if (RelativeLookingAt.Y > 0) {
		return 1;

	}
	else {
		return -1;
	}
}

void AMyDoor::toggleOpen(int Direction) {
	OpenState = !OpenState;
	SetActorRotation(InitialRotation + FRotator(0,90,0)*OpenState*Direction);
	if (OpenSound) {
		UGameplayStatics::PlaySoundAtLocation(this, OpenSound, GetActorLocation());
	}

}