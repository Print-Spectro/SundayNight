//Grabber component can be attached to a pawn to grab other physics actors

#include "Grabber.h"
#include "MyPhysicsProp.h"
#include "DrawDebugHelpers.h"

UGrabber::UGrabber()
{
	//tick required for grabbing
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle(); //Safety check for physics handle
	if (PhysicsHandle == nullptr) {
		return;
	}
	//Given a pointer to a grabbed component, set the physics handle target location in front of the grabber component offset by the hold distance. 
	if (PhysicsHandle->GetGrabbedComponent() != nullptr) {
		PhysicsHandle->SetTargetLocationAndRotation(GetComponentLocation() + GetForwardVector() * HoldDistance, PhysicsHandle->GetGrabbedComponent()->GetComponentRotation());
	}
}

void UGrabber::Release() {
	//Releases the grabbed component and turns on player collision
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle == nullptr) {
		UE_LOG(LogTemp, Display, TEXT("UGrabber::Release: No Physics Handle Component on parent Actor"));
		return;
	}
	if (PhysicsHandle->GetGrabbedComponent() != nullptr) {
		UE_LOG(LogTemp, Display, TEXT("Released"));
		PhysicsHandle->GetGrabbedComponent()->WakeAllRigidBodies();
		PhysicsHandle->GetGrabbedComponent()->GetOwner()->Tags.Remove("Grabbed");
		//Re-enable player collision once dropped.
		Cast<AMyPhysicsProp>(PhysicsHandle->GetGrabbedComponent()->GetOwner())->setPlayerCollision(1);
		PhysicsHandle->ReleaseComponent();
	}
}

void UGrabber::Throw() {
	//Releases grabbed component and adds impulse in direction of the grabber component
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
		//Enabling player collision.
		Cast<AMyPhysicsProp>(Grabbed)->setPlayerCollision(1);
		PhysicsHandle->ReleaseComponent();
		UStaticMeshComponent* GrabbedComponent = Grabbed->FindComponentByClass<UStaticMeshComponent>();
		if (ThrowImpulse / GrabbedComponent->GetMass() > MaximumThrowVelocity) {//impulse over mass gives velocity
			//Preventing throws from going over maximum velocity
			GrabbedComponent->AddImpulse(MaximumThrowVelocity * GetForwardVector(), TEXT("Root"), true);
		}
		else {
			//Throwing with impulse means heavier objects move less
			GrabbedComponent->AddImpulse(ThrowImpulse * GetForwardVector());
		}
	}
}

void UGrabber::Grab() {
	//Grabs hit component with the physics handle
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
		//Disabling player collision so that they don't go on a magic carpet ride
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
		//Returns physics handle component connected to the player
	UPhysicsHandleComponent* Result = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();//constructor making the physics handle I guess 
	if (Result == nullptr) {
		//Very useful if you forget to connect a physics handle to your character
		UE_LOG(LogTemp, Error, TEXT("UGrabber::GetPhysicsHandle: Grabber requires a UPhysicsHandleComponent"));
	}
	return Result;
}

//sweeps for actors by channel 1
bool UGrabber::GetGrabbableInReach(FHitResult& OutHitResult) const {
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxGrabDistance;
	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);
	return GetWorld()->SweepSingleByChannel(
		OutHitResult,
		Start, End,
		FQuat::Identity,
		ECC_GameTraceChannel1,
		Sphere
	);
}