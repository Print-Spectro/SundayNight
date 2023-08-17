// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "MyPhysicsProp.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle == nullptr) {
		return;
	}
	if (PhysicsHandle->GetGrabbedComponent() != nullptr) {
		PhysicsHandle->SetTargetLocationAndRotation(GetComponentLocation() + GetForwardVector() * HoldDistance, PhysicsHandle->GetGrabbedComponent()->GetComponentRotation());
	}

}
void UGrabber::Release() {
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle == nullptr) {
		return;
		UE_LOG(LogTemp, Display, TEXT("No Physics Handle Component on Actor"));
	}
	if (PhysicsHandle->GetGrabbedComponent() != nullptr) {
		UE_LOG(LogTemp, Display, TEXT("Released"));
		PhysicsHandle->GetGrabbedComponent()->WakeAllRigidBodies();
		PhysicsHandle->GetGrabbedComponent()->GetOwner()->Tags.Remove("Grabbed");
		Cast<AMyPhysicsProp>(PhysicsHandle->GetGrabbedComponent()->GetOwner())->setPlayerCollision(1);
		PhysicsHandle->ReleaseComponent();
		
	}

}

void UGrabber::Throw() {
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle == nullptr) {
		return;
		UE_LOG(LogTemp, Display, TEXT("No Physics Handle Component on Actor"));
	}
	if (PhysicsHandle->GetGrabbedComponent() != nullptr) {
		UE_LOG(LogTemp, Display, TEXT("Released"));
		PhysicsHandle->GetGrabbedComponent()->WakeAllRigidBodies();
		PhysicsHandle->GetGrabbedComponent()->GetOwner()->Tags.Remove("Grabbed");
		PhysicsHandle->GetGrabbedComponent()->GetOwner()->Tags.Add("Thrown");
		AActor* Grabbed = PhysicsHandle->GetGrabbedComponent()->GetOwner();
		Cast<AMyPhysicsProp>(Grabbed)->setPlayerCollision(1);
		PhysicsHandle->ReleaseComponent();
		Grabbed->FindComponentByClass<UStaticMeshComponent>()->AddImpulse(100000 * GetForwardVector());
		
	}

}

void UGrabber::Grab() {
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle == nullptr) {
		return;
	}
	FHitResult HitResult;
	bool HasHit = GetGrabbableInReach(HitResult);

	if (HasHit) {
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		HitComponent->WakeAllRigidBodies();
		HitResult.GetActor()->Tags.Add("Grabbed");
		Cast<AMyPhysicsProp>(HitResult.GetActor())->setPlayerCollision(0);
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			HitComponent,
			NAME_None,
			HitResult.ImpactPoint,
			HitComponent->GetComponentRotation()
		);
		//DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 10, FColor::Purple, false, 5);
		//DrawDebugSphere(GetWorld(), HitResult.Location, 10, 10, FColor::Green, false, 5);
		UE_LOG(LogTemp, Display, TEXT("Hit detected on %s"), *HitResult.GetActor()->GetActorNameOrLabel()); //print actor that was hit
	}
	else {
		UE_LOG(LogTemp, Display, TEXT("No Actor Hit"));
	}
}


	UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const {
		UPhysicsHandleComponent* Result = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();//constructor making the physics handle I guess 
		if (Result == nullptr) {
			UE_LOG(LogTemp, Error, TEXT("Grabber requires a UPhysicsHandleComponent."));
		}
		return Result;
	}
	//sweeps for actors by channel 2
	bool UGrabber::GetGrabbableInReach(FHitResult & OutHitResult) const {
		FVector Start = GetComponentLocation();
		FVector End = Start + GetForwardVector() * MaxGrabDistance;
		DrawDebugLine(GetWorld(), Start, End, FColor::Red);
		DrawDebugSphere(GetWorld(), End, 10, 10, FColor::Blue, false, 5);
		FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);
		return GetWorld()->SweepSingleByChannel(
			OutHitResult,
			Start, End,
			FQuat::Identity,
			ECC_GameTraceChannel1,
			Sphere
		);

	}