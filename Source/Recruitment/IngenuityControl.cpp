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
	}
}

void AIngenuityControl::SendNewPosition(FTransform Transform)
{
	TransformPipe.Add(Transform);
}

void AIngenuityControl::SetGrounded(bool isGrounded) {
	Grounded = isGrounded;
}

bool AIngenuityControl::GetGrounded() {
	return Grounded;
}

void AIngenuityControl::CalculateMovement() {
	//Get the target positions
	float xTranslation = TransformPipe[0].GetTranslation().X;
	float yTranslation = TransformPipe[0].GetTranslation().Y;
	float zTranslation = TransformPipe[0].GetTranslation().Z;
	//Control craft horizontally and vertically
	ExeCuteVerticalControl(zTranslation);
	ExecuteHorizontalControl(xTranslation, yTranslation);
	
	TransformPipe.RemoveAt(0);
}

void AIngenuityControl::CheckGrounded() {
	if (TransformPipe.Last().AreTranslationsEqual(GetTransform(), TransformPipe.Last())) {
		Grounded = true;
		TransformPipe.Empty();
		counter = 0.0f;
	}
	TransformPipe.RemoveAt(0);
}

void AIngenuityControl::ExeCuteVerticalControl(float zTransGoal) {
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

void AIngenuityControl::ExecuteHorizontalControl(float xTransGoal, float yTransGoal) {
	float kp = 1;
	float po = 0;

	float ownX = MeshComp->GetComponentLocation().X;
	float xDist = xTransGoal - ownX;

	float targetXVelocity = xDist;
	float ownXVelocity = MeshComp->GetComponentVelocity().X;
	float xVelocityDiff = targetXVelocity - ownXVelocity;


	float ownY = MeshComp->GetComponentLocation().Y;
	float yDist = yTransGoal - ownY;

	float targetYVelocity = yDist;
	float ownYVelocity = MeshComp->GetComponentVelocity().Y;
	float yVelocityDiff = targetYVelocity - ownYVelocity;

	float angleY = -kp * xVelocityDiff/5 + po;
	float angleX = kp * yVelocityDiff/5 + po;

	MeshComp->SetWorldRotation(FRotator(angleY, 0, angleX));
}

