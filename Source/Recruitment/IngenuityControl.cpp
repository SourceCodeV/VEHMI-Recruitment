// Fill out your copyright notice in the Description page of Project Settings.


#include "IngenuityControl.h"

// Sets default values
AIngenuityControl::AIngenuityControl()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AIngenuityControl::BeginPlay()
{
	Super::BeginPlay();
	

	MeshComp = Cast<UStaticMeshComponent>(GetDefaultSubobjectByName(TEXT("Body")));

}

// Called every frame
void AIngenuityControl::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!TransformPipe.IsEmpty() && counter < 1.0f) {
		counter += DeltaTime;
	}
	else if (!TransformPipe.IsEmpty()) {
		CalculateMovement();
		CheckLanding();
	}
}

void AIngenuityControl::SendNewPosition(FTransform Transform)
{
	TransformPipe.Add(Transform);
}

void AIngenuityControl::TakeOff() {
	float ownZ = MeshComp->GetComponentLocation().Z;
	ExecuteVerticalControl(ownZ+1);
	Grounded = false;
}

bool AIngenuityControl::GetGrounded() {
	return Grounded;
}

void AIngenuityControl::SetGrounded(bool isGrounded) {
	Grounded = isGrounded;
}

bool AIngenuityControl::GetLanding() {
	return Landing;
}

void AIngenuityControl::SetLanding(bool isLanding) {
	Landing = isLanding;
}

void AIngenuityControl::Rotate(float amount) {
	Zrotation += amount;
}

void AIngenuityControl::CalculateMovement() {
	//Get the target positions
	float xTranslation = TransformPipe[0].GetTranslation().X;
	float yTranslation = TransformPipe[0].GetTranslation().Y;
	float zTranslation = TransformPipe[0].GetTranslation().Z;
	float zRotation = TransformPipe[0].GetRotation().Z;
	//Control craft horizontally and vertically
	ExecuteVerticalControl(zTranslation);
	ExecuteHorizontalControl(xTranslation, yTranslation, zRotation);
	
	TransformPipe.RemoveAt(0);
}


void AIngenuityControl::CheckLanding() {
	if (Landing) {
		FVector StartPoint = MeshComp->GetComponentLocation();
		FVector EndPoint = StartPoint + FVector(0, 0, -5);
		FHitResult result;
		GetWorld()->LineTraceSingleByChannel(result, StartPoint, EndPoint, ECC_WorldStatic);
		
		if (result.IsValidBlockingHit()) {
			SetGrounded(true);
			SetDroneThrust(0);
			TransformPipe.Empty();
			SetLanding(false);
		}
	}
}

void AIngenuityControl::ExecuteVerticalControl(float zTransGoal) {
	float distanceSpeedConversion = 1 / 15;

	float ownZ = MeshComp->GetComponentLocation().Z;
	float zDist = zTransGoal - ownZ;

	float targetVelocity = zDist ;
	float ownVelocity = MeshComp->GetComponentVelocity().Z;
	float velocityDiff = targetVelocity - ownVelocity;

	float po = 937.5;
	float kp = 100;

	float p = kp * velocityDiff + po;
	SetDroneThrust(p);
}

void AIngenuityControl::ExecuteHorizontalControl(float xTransGoal, float yTransGoal, float zRotation) {
	float kp = 1;
	float po = 0;

	float ownX = MeshComp->GetComponentLocation().X;
	float targetXVelocity = xTransGoal - ownX;

	float ownXVelocity = MeshComp->GetComponentVelocity().X;
	float xVelocityDiff = targetXVelocity - ownXVelocity;

	float ownY = MeshComp->GetComponentLocation().Y;
	float targetYVelocity = yTransGoal - ownY;

	float ownYVelocity = MeshComp->GetComponentVelocity().Y;
	float yVelocityDiff = targetYVelocity - ownYVelocity;

	float angleY = -kp * xVelocityDiff/5 + po;
	float angleX = kp * yVelocityDiff/5 + po;

	MeshComp->SetRelativeRotation(FRotator(0, zRotation * 360 / PI, 0));
	MeshComp->AddWorldRotation(FRotator(angleY, 0, angleX));
}

