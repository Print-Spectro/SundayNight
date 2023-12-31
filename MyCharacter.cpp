// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include <EnhancedInputComponent.h>
#include <EnhancedInputSubsystems.h>
#include "EnhancedInput/Public/EnhancedInputComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "InputActionValue.h"
#include "MyInputConfigData.h"
#include "Camera/CameraComponent.h"
#include "Grabber.h"
#include "MyNoiseMaker.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "MyOutliner.h"
#include "Components/CapsuleComponent.h"
#include "MyPhysicsProp.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));

	CapsuleComponent = Cast<UCapsuleComponent>(RootComponent);
	PlayerCamera->SetupAttachment(CapsuleComponent);
	PlayerCamera->bUsePawnControlRotation = true;

	GrabComponent = CreateDefaultSubobject<UGrabber>(TEXT("GrabComponent"));
	GrabComponent->SetupAttachment(PlayerCamera);

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->SetupAttachment(CapsuleComponent);
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	//Retrieving all the noise makers in the level
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyNoiseMaker::StaticClass(), FoundNoiseMakers);
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyPhysicsProp::StaticClass(), FoundPhysicsProps);
	playNoise();
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//When the noise stops, wait then play noise at a random noise maker
	if (CurrentNoiseMaker != nullptr && !CurrentNoiseMaker->Active) {
		if (!GetWorld()->GetTimerManager().IsTimerActive(NoiseTimer))
		{
			GetWorld()->GetTimerManager().SetTimer(NoiseTimer, this, &AMyCharacter::playNoise, NoiseDelay, false, NoiseDelay);
		}
	}
	//Set render custom depth to outline while hovering, if hover target changes, turn off outline
	hoverOutlineInteractable();
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Get player controller
	APlayerController* PC = Cast<APlayerController>(GetController());

	// Get the local player subsystem
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());

	//Clear out existing mapping, and add our mapping
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMapping, 0);

	//Getting the EnhancedInputComponent
	UEnhancedInputComponent* PEI = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	//Binding the actions
	PEI->BindAction(InputActions->InputMove, ETriggerEvent::Triggered, this, &AMyCharacter::Move);
	PEI->BindAction(InputActions->InputMove, ETriggerEvent::Started, this, &AMyCharacter::walkSound);
	PEI->BindAction(InputActions->InputMove, ETriggerEvent::Completed, this, &AMyCharacter::stopWalkSound);
	PEI->BindAction(InputActions->InputLook, ETriggerEvent::Triggered, this, &AMyCharacter::Look);
 	PEI->BindAction(InputActions->InputGrab, ETriggerEvent::Started, this, &AMyCharacter::grab);
	PEI->BindAction(InputActions->InputGrab, ETriggerEvent::Completed, this, &AMyCharacter::release);
 	PEI->BindAction(InputActions->InputJump, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	PEI->BindAction(InputActions->InputJump, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	PEI->BindAction(InputActions->InputRelease, ETriggerEvent::Triggered, GrabComponent, &UGrabber::Release);
	PEI->BindAction(InputActions->InputInteract, ETriggerEvent::Started, this, &AMyCharacter::interact);
}

void AMyCharacter::Move(const FInputActionValue& Value)
{
	//UE_LOG(LogTemp, Display, TEXT("MoveTriggered"));
	if (Controller!= nullptr)
	{
		const FVector2D MoveValue = Value.Get<FVector2D>();
		const FRotator MovementRotation(0, Controller->GetControlRotation().Yaw, 0);
		//Forward/Backward direction
		if (MoveValue.Y != 0.f || MoveValue.X != 0.f)
		{
			//Get forward vector
			const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);
			AddMovementInput(ForwardDirection, MoveValue.Y);
			//Get right vector
			const FVector SideDirection = MovementRotation.RotateVector(FVector::RightVector);

			AddMovementInput(SideDirection, MoveValue.X);
		}
	}
}
//Very simple walking sound functionality
void AMyCharacter::walkSound() {
	AudioComponent->Play();
}

void AMyCharacter::stopWalkSound() {
	AudioComponent->Stop();
}

void AMyCharacter::Look(const FInputActionValue& Value)
	//Axes 2D input action bound to controller input
{
	FVector2D LookValue = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookValue.X);
		AddControllerPitchInput(LookValue.Y);
	}
}

void AMyCharacter::grab(const FInputActionValue& Value) {
	//See Grabber component
	GrabComponent->Grab();
}

void AMyCharacter::release() {
	//See Grabber component
	GrabComponent->Throw();
}

void AMyCharacter::playNoise() {
	//Randomly chooses a noise maker in the world to play a noise
	GetWorld()->GetTimerManager().SetTimer(NoiseTimer, this, &AMyCharacter::wakeUp, 1, false, 1);
	GetWorld()->GetTimerManager().ClearTimer(ScoreTimer);
	if (FoundNoiseMakers.Num() > 0) {
		int RandomIndex = FMath::RandRange(0, FoundNoiseMakers.Num() - 1);
		AMyNoiseMaker* RandomActor = Cast<AMyNoiseMaker>(FoundNoiseMakers[RandomIndex]);
		if (RandomActor) {
			RandomActor->activate();
			CurrentNoiseMaker = RandomActor;
		}
	}
}

void AMyCharacter::increaseScore(){
	score++;
}

void AMyCharacter::startIncreaseScore() {
	//Increments score using increaseScore function bound to a timer
	if (!GetWorld()->GetTimerManager().IsTimerActive(ScoreTimer)) {
		GetWorld()->GetTimerManager().SetTimer(ScoreTimer, this, &AMyCharacter::increaseScore, 1, true, 0);
	}
}

AActor* AMyCharacter::getInteractableLookingAt() {
	//Returns pointer to actors in the interactable trace channel
	ECC_GameTraceChannel2;
	FHitResult HitResult;
	FVector Start = PlayerCamera->GetComponentLocation();
	FVector End = Start + PlayerCamera->GetForwardVector() * InteractDistance;
	FCollisionShape Sphere = FCollisionShape::MakeSphere(20);
	GetWorld()->SweepSingleByChannel(HitResult, Start, End, FQuat::Identity, ECC_GameTraceChannel2, Sphere);
	return HitResult.GetActor();
}

void AMyCharacter::wakeUp() {
	//Player possesses character in order to "wake up" from the possessed bed actor
	if (UGameplayStatics::GetPlayerPawn(GetWorld(), 0) != this) {
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->Possess(this);
	}
}

void AMyCharacter::interact() {
	//Bound in blueprints using an interface
}

void AMyCharacter::restartLevel() {
	//Opens current level 
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

void AMyCharacter::hoverOutlineInteractable(){
	//Turns on render custom depth when looking at an intractable actor, enabling outline post process materials. 
	AActor* LookingAt = getInteractableLookingAt();
	if (LookingAt == nullptr) {
		if (PreviousHovered != nullptr) {
			PreviousHovered->setOutline(0); //No hovered means hovering ended: turn off outline
		}
		return;
	}
	UMyOutliner* OutlineComponent = LookingAt->FindComponentByClass<UMyOutliner>();
	if (OutlineComponent == nullptr) {
			return;
			UE_LOG(LogTemp, Warning, TEXT("Interactable actor has no outline component"))
	}
	if (PreviousHovered == OutlineComponent) {
		OutlineComponent->setOutline(1);
	}
	if (PreviousHovered != OutlineComponent){ 
		//this statement handles the case of moving between two overlapping interactables.
		if (PreviousHovered != nullptr) {
			PreviousHovered->setOutline(0); 
		}
	}
	PreviousHovered = OutlineComponent;
}


