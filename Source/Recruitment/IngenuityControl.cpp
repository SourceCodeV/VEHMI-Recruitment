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

	//Meshcomp = Cast<UStaticMeshComponent>(GetDefaultSubobjectByName(TEXT("CombinedMesh")));

}

// Called every frame
void AIngenuityControl::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//CalculateMovement();
	//if (!TransformPipe.IsEmpty() && counter < 1.0f) {
	//	counter += DeltaTime;
	//}
	//else if (!TransformPipe.IsEmpty()) {
	//	CalculateMovement();
	//	CheckSamePosition();
	//}
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
	//Basic follow after one second set position
	//SetActorTransform(TransformPipe[0]);

	//Meshcomp->SetWorldTransform(TransformPipe[0]);
	//const FVector Up = this->GetActorUpVector();
	//const FVector Force = FVector(0, 0, 100);
	//FVector result = Up * Force;
	//float mass = Meshcomp->GetMass();
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, Meshcomp->GetName());
	//Meshcomp->AddForce(Up * Force);
}

void AIngenuityControl::CheckSamePosition() {
	if (TransformPipe.Last().AreTranslationsEqual(GetTransform(), TransformPipe.Last())) {
		AtSamePosition = true;
		TransformPipe.Empty();
		counter = 0.0f;
	}
	TransformPipe.RemoveAt(0);
}