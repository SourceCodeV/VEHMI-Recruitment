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

void AIngenuityControl::SetAtSamePosition(bool inAtSamePosition) {
	AtSamePosition = inAtSamePosition;
}

bool AIngenuityControl::GetAtSamePosition() {
	return AtSamePosition;
}

void AIngenuityControl::CalculateMovement() {
	SetActorTransform(TransformPipe[0]);
	if (TransformPipe.Last().AreTranslationsEqual(GetTransform(), TransformPipe.Last())) {
		AtSamePosition = true;
		TransformPipe.Empty();
		counter = 0.0f;
	}
	else {
		TransformPipe.RemoveAt(0);
	}
}
