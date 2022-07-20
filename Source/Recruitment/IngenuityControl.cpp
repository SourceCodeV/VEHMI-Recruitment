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

}

void AIngenuityControl::SendNewPosition(FVector Position, float DeltaTime)
{
	if (counter < 1.0f && !AtSamePosition) {
		counter
	}
}

void AIngenuityControl::SetAtSamePosition(bool inAtSamePosition) {
	AtSamePosition = inAtSamePosition;
}

bool AIngenuityControl::GetAtSamePosition() {
	return AtSamePosition;
}

